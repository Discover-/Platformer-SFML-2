#include <SFML/Graphics.hpp>
#include "menubutton.h"
#include "menumanager.h"

MenuButton::MenuButton(int _buttonId, sf::Texture _buttonTexture, sf::Vector2f position)
{
    buttonId = _buttonId;
    buttonTexture = _buttonTexture;
    SetPosition(position.x, position.y);
    isCollapsed = false;
}

MenuButton::~MenuButton()
{
    for (std::vector<MenuButton*>::iterator itr = childButtons.begin(); itr != childButtons.end(); ++itr)
        delete *itr;
}
