#include "mainmenustate.hpp"

MainMenuState::MainMenuState(sf::RenderWindow* renderWindow, StateManager* manager) : m_manager(manager), m_window(renderWindow),
//!Create Main menu
m_mainMenu(&m_manager->resourceManager),
//!Create the levelSelection menu
m_levelSelectionMenu(&m_manager->resourceManager),
currentSubMenu(&m_mainMenu)
{
    //Set the callbacks for mainMenu
    m_mainMenu.button_play.setCallback(&play, this);
    m_mainMenu.button_options.setCallback(&options, this);
    m_mainMenu.button_levelEditor.setCallback(&levelEditor, this);
    m_mainMenu.button_exit.setCallback(&exit, this);

    //Set the callbacks for the levelSelectionMenu
    m_levelSelectionMenu.button_backToMenu.setCallback(&backToMain, this);
    m_levelSelectionMenu.button_level1.setCallback(&level1, this);

    gameState = GAME_STATE_MENU;
}

MainMenuState::~MainMenuState()
{
    //delete currentSubMenu;
}

void MainMenuState::handle_events()
{
    sf::Event _event;

    while (m_window->pollEvent(_event))
    {
        currentSubMenu->handle_event(_event);

        switch (_event.type)
        {
            case sf::Event::Closed:
            {
                m_manager->set_next_state(GAME_STATE_EXIT);
                break;
            }
        }
    }
}

void MainMenuState::logic(double passed, double deltaTime)
{

}

void MainMenuState::render(double alpha)
{
    m_window->clear();
    m_window->draw(*currentSubMenu);
    m_window->display();
}

void MainMenuState::play(void* inst, Button* button)
{
    ((MainMenuState*)inst)->currentSubMenu = &((MainMenuState*)inst)->m_levelSelectionMenu;
}

void MainMenuState::options(void* inst, Button* button)
{
    ((MainMenuState*)inst)->m_manager->set_next_state(GAME_STATE_OPTIONS);
}

void MainMenuState::levelEditor(void* inst, Button* button)
{
    ((MainMenuState*)inst)->m_manager->set_next_state(GAME_STATE_LEVEL_EDITOR);
}

void MainMenuState::exit(void* inst, Button* button)
{
    ((MainMenuState*)inst)->m_manager->set_next_state(GAME_STATE_EXIT);
}

//! BEGIN LEVELSELECTIONMENU
void MainMenuState::backToMain(void* inst, Button* button)
{
    ((MainMenuState*)inst)->currentSubMenu = &((MainMenuState*)inst)->m_mainMenu;
}

void MainMenuState::level1(void* inst, Button* button)
{
    ((MainMenuState*)inst)->m_manager->set_next_state(GAME_STATE_GAME);
}
