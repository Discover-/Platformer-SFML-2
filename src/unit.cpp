#include "statemanager.hpp"
#include "unit.hpp"
#include "leveleditorstate.hpp"

Unit::Unit(sf::RenderWindow* _window, sf::Vector2f position, sf::RectangleShape body, StateManager* _manager, GameState* _gameState /* = NULL */)
{
    SetPosition(position.x, position.y);
    m_window = _window;
    bodyShape = body;
    m_manager = _manager;
    gameState = _gameState;

    isJumping = false;
    jumpSpeed = 15;
    isFalling = false;
    fallSpeed = 0;
}

void Unit::Update()
{
    std::vector<SpriteInfo> sprites;
    
    if (gameState)
        sprites = ((LevelEditorState*)gameState)->GetSprites();

    if (isJumping)
    {
        if (jumpSpeed && !CollidesWithGameobjects(sprites, GetPositionX(), GetPositionY() - jumpSpeed))
        {
            SetPositionY(GetPositionY() - jumpSpeed);
            jumpSpeed--;
        }
        else
        {
            isJumping = false;
            isFalling = true;
            jumpSpeed = 15;
        }
    }
    else
    {
        if (!CollidesWithGameobjects(sprites, GetPositionX(), GetPositionY() + fallSpeed))
        {
            isFalling = true;
            SetPositionY(GetPositionY() + fallSpeed);
            fallSpeed++;
        }
        else
        {
            isFalling = false;
            fallSpeed = 0;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
        SetPositionY(GetPositionY() - 10.0f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
        SetPositionY(GetPositionY() + 10.0f);
}

bool Unit::CollidesWithGameobjects(float newPosX /* = 0.0f */, float newPosY /* = 0.0f */)
{
    float positionToCheckX = GetPositionX();
    float positionToCheckY = GetPositionY();

    if (newPosX != 0.0f && newPosY != 0.0f)
    {
        positionToCheckX = newPosX;
        positionToCheckY = newPosY;
    }

    if (positionToCheckX < 0.1f || positionToCheckY < 0.1f || positionToCheckX > 900.0f || positionToCheckY > 525.0f)
        return true;

    //! TODO: add gameobject collision checks here
    return false;
}

bool Unit::CollidesWithGameobjects(std::vector<SpriteInfo> sprites, float newPosX /* = 0.0f */, float newPosY /* = 0.0f */)
{
    if (sprites.empty())
        return CollidesWithGameobjects(newPosX, newPosY);

    float positionToCheckX = GetPositionX();
    float positionToCheckY = GetPositionY();

    if (newPosX != 0.0f && newPosY != 0.0f)
    {
        positionToCheckX = newPosX;
        positionToCheckY = newPosY;
    }

    if (positionToCheckX < 0.1f || positionToCheckY < 0.1f || positionToCheckX > 900.0f || positionToCheckY > 525.0f)
        return true;

    for (std::vector<SpriteInfo>::iterator itr = sprites.begin(); itr != sprites.end(); ++itr)
    {
        if (!(*itr).isCollidable)
            continue;

        sf::Sprite sprite(m_manager->resourceManager.getTexture((*itr).filename));
        sf::FloatRect tileRect = sprite.getGlobalBounds();
        sf::FloatRect playerRect = bodyShape.getGlobalBounds();

        if (WillCollision(positionToCheckY, positionToCheckY, playerRect.height, playerRect.width, (*itr).position.x, (*itr).position.y, tileRect.height, tileRect.width))
            return true;
    }

    //! TODO: add gameobject collision checks here
    return false;
}

void Unit::Jump()
{
    isJumping = true;
    fallSpeed = 0;
    jumpSpeed = 15;
}
