#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "statemanager.hpp"

/// \brief State base class
class GameState
{
    public:
        virtual ~GameState() { };

        ///\brief Handle the events(keypresses etc)
        virtual void handle_events() = 0;
        ///\brief Do the logic(physics etc.), gets the time passed since the last logic update, consume this in deltaTime sized chunks
        virtual void logic(double passed, double deltaTime) = 0;

        ///\brief Draw function(interpolate and render everything on the window given at creation)
        ///A note on the interpolation:
        ///The render state = currentstate * alpha - previousstate * ( 1 - alpha )
        ///Example: renderPos = currentPos * alpha - previousPos * ( 1 - alpha )
        virtual void render(double alpha) = 0;

    protected:
        StateManager* m_manager;
};

#endif // GAMESTATE_HPP_INCLUDED
