#pragma once

#include <vector>

#include "gamestate.hpp"
#include "player.hpp"
#include "button.hpp"
#include "gameminimenu.hpp"

class Game : public GameState
{
    public:
        Game(sf::RenderWindow* renderWindow, StateManager* manager);
        ~Game();

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha);

        bool IsGamePaused() { return m_PausedGame; }
        std::vector<CollidableObject>& GetCollidableObjects() { return collidableObjects; }

        static void resume(void* inst, Button* button, sf::Event& event);
        static void backToMenu(void* inst, Button* button, sf::Event& event);
        static void exit(void* inst, Button* button, sf::Event& event);

    private:
        StateManager* m_manager;
        sf::RenderWindow* m_window;

        bool m_PausedGame;

        GameMiniMenu* m_gameMiniMenu;
        sf::RectangleShape m_miniMenuBackground;

        Player* player;
        sf::Color m_color; //Just to show the logic function
        std::vector<CollidableObject> collidableObjects;
};
