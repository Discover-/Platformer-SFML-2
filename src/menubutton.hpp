#pragma once

#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "position.hpp"

class MenuManager;

class MenuButton : public Position
{
    public:
        MenuButton(int _buttonId, std::string _textureFilename, sf::Vector2f position);
        ~MenuButton();

        std::string GetTextureFilename() { return textureFilename; }

        std::vector<MenuButton*>& GetChildButtons() { return childButtons; }
        void SetChildButtons(std::vector<MenuButton*> _childButtons) { childButtons = _childButtons; }
        void AddChildButton(MenuButton* menuButton) { childButtons.push_back(menuButton); }

        bool HasChildButtons() { return childButtons.size() > 0; }
        bool IsCollapsed() { return isCollapsed; }
        void SetIsCollapsed(bool val) { isCollapsed = val; }

        int GetButtonId() { return buttonId; }

    private:
        std::vector<MenuButton*> childButtons;
        std::string textureFilename;
        bool isCollapsed;
        int buttonId;
};
