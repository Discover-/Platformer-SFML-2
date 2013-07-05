#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "statemanager.hpp"
#include "inlinefunctions.hpp"

Game::Game(sf::RenderWindow* window, StateManager* manager)
{
    m_manager = nullptr;
    m_window = nullptr;
    m_window = window;
    m_manager = manager;

    m_color.r = 255;
    player = NULL;

    sf::Vector2f buttonPositions[3];
    buttonPositions[0] = sf::Vector2f(463.0f, 270.0f);
    buttonPositions[1] = sf::Vector2f(432.0f, 300.0f);
    buttonPositions[2] = sf::Vector2f(481.0f, 330.0f);

    m_gameMiniMenu = new GameMiniMenu(&m_manager->resourceManager, buttonPositions);
    m_gameMiniMenu->button_resume.setCallback(&resume, this);
    m_gameMiniMenu->button_backToMenu.setCallback(&backToMenu, this);
    m_gameMiniMenu->button_exit.setCallback(&exit, this);

    m_miniMenuBackground.setPosition(sf::Vector2f(400.0f, 240.0f));
    m_miniMenuBackground.setSize(sf::Vector2f(200.0f, 150.0f));
    m_miniMenuBackground.setFillColor(sf::Color::White);
    m_miniMenuBackground.setFillColor(sf::Color(255, 255, 255, 128));

    m_PausedGame = false;

    gameState = GAME_STATE_GAME;
}

Game::~Game()
{
    delete player;
    delete m_gameMiniMenu;
}

void Game::handle_events()
{
    sf::Event _event;

    while (m_window->pollEvent(_event))
    {
        if (m_PausedGame)
            m_gameMiniMenu->handle_event(_event);

        switch (_event.type)
        {
            case sf::Event::Closed:
                //! Set the manager to shut down
                m_manager->set_next_state(GAME_STATE_EXIT);
                break;
            case sf::Event::KeyReleased:
            {
                switch (_event.key.code)
                {
                    case sf::Keyboard::Escape:
                        m_PausedGame = !m_PausedGame;
                        break;
                    default:
                        break;
                }
                break;
            }
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

    if (!player)
    {
        sf::RectangleShape bodyShape(sf::Vector2f(75.0f, 75.0f));
        bodyShape.setFillColor(sf::Color::Green);
        player = new Player(m_window, sf::Vector2f(500.0f, 300.0f), bodyShape, m_manager, this);
    }

    player->Update();
}

void Game::render(double alpha)
{
    m_window->clear(m_color);

    if (player)
    {
        sf::RectangleShape rectShape = player->GetBodyShape();
        rectShape.setPosition(player->GetPosition());
        m_window->draw(rectShape);
    }

    if (m_PausedGame)
    {
        m_window->draw(m_miniMenuBackground);
        m_window->draw(*m_gameMiniMenu);
    }

    m_window->display();
}

void Game::resume(void* inst, Button* button)
{
    ((Game*)inst)->m_PausedGame = false;
}

void Game::backToMenu(void* inst, Button* button)
{
    ((Game*)inst)->m_manager->set_next_state(GAME_STATE_MENU);
}

void Game::exit(void* inst, Button* button)
{
    ((Game*)inst)->m_manager->set_next_state(GAME_STATE_EXIT);
}
