#include "player.hpp"
#include "leveleditorstate.hpp"
#include "inlinefunctions.hpp"
#include "game.hpp"

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
    bool levelEditor = gameState->GetState() == GAME_STATE_LEVEL_EDITOR;

    if (IsDead() || (!levelEditor && ((Game*)gameState)->IsGamePaused()))
        return;

    std::vector<CollidableObject> sprites = levelEditor ? ((LevelEditorState*)gameState)->GetCollidableObjects() : ((Game*)gameState)->GetCollidableObjects();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        if (!CollidesWithGameobjects(sprites, GetPositionX() - 5.0f, GetPositionY()))
            SetPosition(GetPositionX() - 5.0f, GetPositionY());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        if (!CollidesWithGameobjects(sprites, GetPositionX() + 5.0f, GetPositionY()))
            SetPosition(GetPositionX() + 5.0f, GetPositionY());

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !IsJumping())
        Jump();
}
