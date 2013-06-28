#include "statemanager.hpp"
#include "gamestate.hpp"
#include "game.hpp"
#include "menumanager.hpp"

StateManager::StateManager()
{
    m_window = 0;
    stateID = 0;
    nextState = 0;
    m_currentState = 0;
}

void StateManager::clean()
{
    delete m_window;
    delete m_currentState; //Make sure the destructor of the state is well-written
}

void StateManager::mainLoop()
{
    m_window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Platformer C++ SFML", sf::Style::Close);

    sf::Clock clock;

    double t = 0.0;
    const double dt = 1 / TICKS_PER_SECOND;

    double currentTime = clock.getElapsedTime().asSeconds();
    double accumulator = 0.0;

    while (stateID != STATE_EXIT)
    {
        //Change state if needed
        change_state();

        double newTime = clock.getElapsedTime().asSeconds();
        double frameTime = newTime - currentTime;

        if (frameTime > 0.25)
            frameTime = 0.25; //max frame time to avoid spiral of death

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt)
        {
            m_currentState->handle_events();
            m_currentState->logic(t, dt);
            t += dt;
            accumulator -= dt;
        }

        const double alpha = accumulator / dt;
        m_currentState->render(alpha);
    }

    //End of the line, let's clean our mess and shut down
    m_window->close();
    clean();
}

//State status manager
void StateManager::set_next_state(int newState)
{
    //If the user doesn't want to exit
    if (nextState != STATE_EXIT)
    {
        //Set the next state
        nextState = newState;
    }
}

//State changer
void StateManager::change_state()
{
    //If the state needs to be changed
    if (nextState != STATE_NULL)
    {
        //Delete the current state
        if (nextState != STATE_EXIT)
        {
            delete m_currentState;
            m_currentState = nullptr;
        }

        //Change the state
        switch (nextState)
        {
            /*case STATE_INTRO:
                delete m_currentState;
                m_currentState = new Intro(m_window, this);
                break;*/
            case STATE_MENU:
                m_currentState = new MenuManager(m_window, this);
                break;
            case STATE_GAME:
                m_currentState = new Game(m_window, this);
                break;
        }

        stateID = nextState;
        nextState = STATE_NULL;
    }
}
