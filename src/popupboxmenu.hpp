#ifndef POPUPBOXMENU_HPP_INCLUDED
#define POPUPBOXMENU_HPP_INCLUDED

#include "menu.hpp"
#include "button.hpp"
#include "resourcemanager.hpp"

class PopUpBoxMenu : public Menu
{
    public:
        PopUpBoxMenu(sf::Vector2f positionBtnOne, sf::Vector2f positionBtnTwo);
        PopUpBoxMenu(ResourceManager* resourceManager, sf::Vector2f positionBtnOne, sf::Vector2f positionBtnTwo);

        Button button_yes;
        Button button_no;
};

#endif // POPUPBOXMENU_HPP_INCLUDED
