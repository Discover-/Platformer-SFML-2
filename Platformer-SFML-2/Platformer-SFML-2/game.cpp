#include <SFML/Graphics.hpp>
#include "game.h"
#include "stateManager.h"

Game::Game(sf::RenderWindow* window, StateManager* manager)
{
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
                //Set the manager to shut down
                m_manager->set_next_state(StateManager::GameStates::STATE_EXIT);
                break;
            default:
                break;
        }
    }
}

void Game::logic(double passed, double deltaTime)
{
    //Just to show what kind of things logic should handle, other examples are movement etc
    //don't forget to step in deltaTime sized chunks when working with physics
    if ( m_color.r > 0 )
    {
        m_color.r--;
        m_color.g++;
    }
}

void Game::render(double alpha)
{
    m_window->clear(m_color);
    m_window->display();
}
