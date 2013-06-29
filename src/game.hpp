#pragma once

#include <vector>

#include "gamestate.hpp"
#include "player.hpp"

class Game : public GameState
{
    public:
        Game(sf::RenderWindow* renderWindow, StateManager* manager);

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha);

    private:
        StateManager* m_manager;
        sf::RenderWindow* m_window;
        Player* player;
        sf::Color m_color; //Just to show the logic function
};
