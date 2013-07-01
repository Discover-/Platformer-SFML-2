#include <iostream>

#include "statemanager.hpp"
#include "gamestate.hpp"
#include "game.hpp"
#include "mainmenustate.hpp"
#include "leveleditorstate.hpp"

StateManager::StateManager()
{
    m_window = 0;
    stateID = GAME_STATE_NULL;
    nextState = GAME_STATE_NULL;
    m_currentState = 0;
}

void StateManager::clean()
{
    delete m_window;
    delete m_currentState; //! Make sure the destructor of the state is well-written
}

void StateManager::mainLoop()
{
    m_window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Platformer C++ SFML", sf::Style::Close);
    m_window->setPosition(sf::Vector2i(300, 150));

    sf::Clock clock;

    double t = 0.0;
    double const dt = 1 / TICKS_PER_SECOND;

    double currentTime = clock.getElapsedTime().asSeconds();
    double accumulator = 0.0;

    while (stateID != GAME_STATE_EXIT)
    {
        //! Change state if needed
        change_state();

        double newTime = clock.getElapsedTime().asSeconds();
        double frameTime = newTime - currentTime;

        if (frameTime > 0.25)
            frameTime = 0.25; //! Max frame time to avoid spiral of death

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt)
        {
            m_currentState->handle_events();
            m_currentState->logic(t, dt);

            t += dt;
            accumulator -= dt;
        }

        m_currentState->render(accumulator / dt);
    }

    //! End of the line, let's clean our mess and shut down
    m_window->close();
    clean();
}

//State status manager
void StateManager::set_next_state(GameStates newState)
{
    //If the user doesn't want to exit
    if (nextState != GAME_STATE_EXIT)
    {
        //Set the next state
        nextState = newState;
    }
}

void StateManager::change_state()
{
    //! If the state needs to be changed
    if (nextState != GAME_STATE_NULL)
    {
        //! Delete the current state
        if (nextState != GAME_STATE_EXIT)
        {
            delete m_currentState;
            m_currentState = nullptr;
        }

        //! Change the state
        switch (nextState)
        {
            /*case STATE_INTRO:
                delete m_currentState;
                m_currentState = new Intro(m_window, this);
                break;*/
            case GAME_STATE_MENU:
                m_currentState = new MainMenuState(m_window, this);
                break;
            case GAME_STATE_GAME:
                m_currentState = new Game(m_window, this);
                break;
            case GAME_STATE_LEVEL_EDITOR:
                m_currentState = new LevelEditorState(m_window, this);
                //sf::RenderWindow window2(sf::VideoMode(500, 300), "Platformer C++ SFML - Tileset", sf::Style::Close);
                break;
            case GAME_STATE_EXIT:
                m_window->close();
                break;
            default:
                std::cout << "Unknown nextState in StateManager::change_state(): " << nextState << std::endl;
                return;
        }

        stateID = nextState;
        nextState = GAME_STATE_NULL;
    }
}
