#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "position.hpp"
#include "statemanager.hpp"

class Unit : public Position
{
    public:
        Unit(sf::RenderWindow* _window, sf::Vector2f position, sf::RectangleShape body, StateManager* manager, GameState* _gameState = NULL);
        ~Unit();

        virtual void Update();

        sf::RenderWindow* m_window;

        void JustDied() { m_isAlive = false; }
        void JustRespawned() { m_isAlive = true; }
        bool IsDead() { return !m_isAlive; }

        void Jump();
        bool IsJumping() { return isJumping; }

        sf::RectangleShape GetBodyShape() { return bodyShape; }

        bool CollidesWithGameobjects(float newPosX = 0.0f, float newPosY = 0.0f);
        bool CollidesWithGameobjects(std::vector<std::pair<sf::Vector2f, std::string> > sprites, float newPosX = 0.0f, float newPosY = 0.0f);

        StateManager* m_manager;
        GameState* gameState;

    private:
        sf::RectangleShape bodyShape;
        bool m_isAlive;
        bool isMoving, isJumping, isFalling;
        int fallSpeed, jumpSpeed, bounceSpeed;
};
