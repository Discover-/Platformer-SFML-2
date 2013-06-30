#include "mainmenu.hpp"

MainMenu::MainMenu(sf::RenderWindow* renderWindow, StateManager* manager)
:m_manager(manager),
m_window(renderWindow),
/*Create the buttons*/
m_button_play(sf::Vector2f(300.0f, 100.0f), "Graphics/Menu/play.png", m_manager, &play, this),
m_button_options(sf::Vector2f(300.0f, 200.0f), "Graphics/Menu/options.png", m_manager, &MainMenu::options, this),
m_button_levelEditor(sf::Vector2f(300.0f, 300.0f), "Graphics/Menu/level_editor.png", m_manager, &MainMenu::levelEditor, this),
m_button_exit(sf::Vector2f(300.0f, 400.0f), "Graphics/Menu/quit.png", m_manager, &MainMenu::exit, this)
{
    m_menu.items.push_back(&m_button_play);
    m_menu.items.push_back(&m_button_options);
    m_menu.items.push_back(&m_button_levelEditor);
    m_menu.items.push_back(&m_button_exit);
}

void MainMenu::handle_events()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        m_menu.handle_event(event);
    }
}

void MainMenu::logic(double passed, double deltaTime)
{

}

void MainMenu::render(double alpha)
{
    m_window->clear();
    m_window->draw(m_menu);
    m_window->display();
}

void MainMenu::play(void* inst, Button* button)
{
    MainMenu* self = (MainMenu*) inst;
    self->m_manager->set_next_state(StateManager::GameStates::GAME_STATE_GAME);
}

void MainMenu::options(void* inst, Button* button)
{
    MainMenu* self = (MainMenu*) inst;
    self->m_manager->set_next_state(StateManager::GameStates::GAME_STATE_OPTIONS);
}

void MainMenu::levelEditor(void* inst, Button* button)
{
    MainMenu* self = (MainMenu*) inst;
    self->m_manager->set_next_state(StateManager::GameStates::GAME_STATE_LEVEL_EDITOR);
}

void MainMenu::exit(void* inst, Button* button)
{
    MainMenu* self = (MainMenu*) inst;
    self->m_manager->set_next_state(StateManager::GameStates::GAME_STATE_EXIT);
}
