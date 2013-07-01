#include "player.hpp"
#include "leveleditorstate.hpp"
#include "inlinefunctions.hpp"

Player::Player(sf::RenderWindow* _window, sf::Vector2f position, sf::RectangleShape body, StateManager* manager, GameState* _gameState) :
Unit(_window, position, body, manager)
{
    gameState = _gameState;
}

Player::~Player()
{

}

void Player::Update()
{
    Unit::Update();

    if (IsDead())
        return;

    std::vector<CollidableObject> sprites;
    
    if (gameState)
        sprites = ((LevelEditorState*)gameState)->GetCollidableObjects();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        if (!CollidesWithGameobjects(sprites, GetPositionX() - 5.0f, GetPositionY()))
            SetPosition(GetPositionX() - 5.0f, GetPositionY());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        if (!CollidesWithGameobjects(sprites, GetPositionX() + 5.0f, GetPositionY()))
            SetPosition(GetPositionX() + 5.0f, GetPositionY());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !IsJumping())
        Jump();
}
