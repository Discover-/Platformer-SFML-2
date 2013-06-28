#include <SFML/Graphics.hpp>

#include "leveleditor.hpp"
#include "statemanager.hpp"

LevelEditor::LevelEditor(sf::RenderWindow* window, StateManager* manager)
{
    m_manager = nullptr;
    m_window = nullptr;
    m_window = window;
    m_manager = manager;
}

void LevelEditor::handle_events()
{
    sf::Event _event;

    while (m_window->pollEvent(_event))
    {
        switch (_event.type)
        {
            case sf::Event::Closed:
                //! Set the manager to shut down
                m_manager->set_next_state(StateManager::GameStates::GAME_STATE_EXIT);
                break;
            default:
                break;
        }
    }
}

void LevelEditor::logic(double passed, double deltaTime)
{

}

void LevelEditor::render(double alpha)
{
    m_window->clear(sf::Color::Cyan);
    m_window->display();
}
