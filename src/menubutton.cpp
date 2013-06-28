#include <SFML/Graphics.hpp>

#include <string>

#include "menubutton.hpp"
#include "menumanager.hpp"

MenuButton::MenuButton(int _buttonId, std::string _textureFilename, sf::Vector2f position)
{
    buttonId = _buttonId;
    textureFilename = _textureFilename;
    SetPosition(position.x, position.y);
    isCollapsed = false;
}

MenuButton::~MenuButton()
{
    for (std::vector<MenuButton*>::iterator itr = childButtons.begin(); itr != childButtons.end(); ++itr)
        delete *itr;
}
