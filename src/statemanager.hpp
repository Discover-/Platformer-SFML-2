#ifndef STATEMANAGER_HPP_INCLUDED
#define STATEMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

#include "resourceManager.hpp"

class GameState;
class Game;

#define TICKS_PER_SECOND 25 //Used by the fixed timestep

///\brief A class for handling the switches between states(for example from menu to game)
class StateManager
{
    public:
        ///\brief A list of all the states. Edit this for your own needs, see change_state for more details
        enum GameStates
        {
            STATE_NULL,
            STATE_INTRO,
            STATE_MENU,
            STATE_GAME,
            STATE_EXIT
        };

        StateManager();

        ///\brief Starts the StateManager, this function will return when STATE_EXIT is called(end of the line)
        void start() { mainLoop(); };

        ///\brief Call this from a state when you want to set a different state(this will delete the current state, make sure the destructor is prepared)
        void set_next_state(int newState);

        ResourceManager resourceManager;

    protected:
        ///\brief State changer
        ///See the implementation in stateManager.cpp for more details regarding the construction of the states
        void change_state();

        ///\brief The main loop, this will call all the standard functions from a state(handle_events, logic and render)
        void mainLoop();

        ///\brief Clean up our mess
        void clean();

        sf::RenderWindow* m_window;

        //State variables
        int stateID;
        int nextState;

        //Game state object
        GameState* m_currentState;
};

#endif // STATEMANAGER_HPP_INCLUDED
