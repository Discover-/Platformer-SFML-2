#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "statemanager.hpp"
#include "inlinefunctions.hpp"

/// \brief State base class
class GameState
{
    public:
        virtual ~GameState() { };

        ///\brief Handle the events(keypresses etc)
        virtual void handle_events() = 0;
        ///\brief Do the logic(physics etc.), gets the total time passed, consume this in deltaTime sized chunks
        ///\note THE TOTAL TIME PASSED, *NOT* the time from the last logic call
        virtual void logic(double passed, double deltaTime) = 0;

        ///\brief Draw function(interpolate and render everything on the window given at creation)
        ///A note on the interpolation:
        ///The render state = currentstate * alpha + previousstate * ( 1 - alpha )
        ///Example: renderPos = currentPos * alpha + previousPos * ( 1 - alpha )
        virtual void render(double alpha) = 0;

        GameStates GetState() { return gameState; }

    protected:
        StateManager* m_manager;
        GameStates gameState;
};

#endif // GAMESTATE_HPP_INCLUDED
