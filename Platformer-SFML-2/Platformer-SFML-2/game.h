#pragma once

#include <vector>
#include "gameState.h"

class Game : public GameState
{
    public:
        static Game& instance(sf::RenderWindow* renderWindow, StateManager* manager)
        {
            static Game game(renderWindow, manager);
            return game;
        }

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha);

    private:
        Game(sf::RenderWindow* renderWindow, StateManager* manager);
        ~Game();

        StateManager* m_manager = nullptr;
        sf::RenderWindow* m_window = nullptr;

        sf::Color m_color; //Just to show the logic function
};
