#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "unit.hpp"
#include "statemanager.hpp"


class Player : public Unit
{
    public:
        Player(sf::RenderWindow* _window, sf::Vector2f position, sf::RectangleShape body, StateManager* manager, GameState* _gameState = NULL);
        ~Player();

        void Update();

    private:

};
