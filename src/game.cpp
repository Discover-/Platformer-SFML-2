#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "statemanager.hpp"

Game::Game(sf::RenderWindow* window, StateManager* manager)
{
    m_manager = nullptr;
    m_window = nullptr;
    m_window = window;
    m_manager = manager;

    m_color.r = 255;
}

void Game::handle_events()
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

void Game::logic(double passed, double deltaTime)
{
    //! Just to show what kind of things logic should handle, other examples are movement etc
    //! don't forget to step in deltaTime sized chunks when working with physics
    if (m_color.r > 1)
    {
        m_color.r -= 2;
        m_color.g += 2;
    }
    else
    {
        m_color.r = 255;
        m_color.g = 0;
    }
}

void Game::render(double alpha)
{
    m_window->clear(m_color);
    m_window->display();
}
