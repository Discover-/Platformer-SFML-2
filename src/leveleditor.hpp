#pragma once

#include <vector>

#include "gamestate.hpp"

class LevelEditor : public GameState
{
    public:
        LevelEditor(sf::RenderWindow* renderWindow, StateManager* manager);

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha);

    private:
        StateManager* m_manager;
        sf::RenderWindow* m_window;
};
