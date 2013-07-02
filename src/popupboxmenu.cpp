#include "popupboxmenu.hpp"

PopUpBoxMenu::PopUpBoxMenu(sf::Vector2f positionBtnOne, sf::Vector2f positionBtnTwo)
{
    button_yes.setPosition(positionBtnOne);
    button_no.setPosition(positionBtnTwo);
    items.push_back(&button_yes);
    items.push_back(&button_no);
}

PopUpBoxMenu::PopUpBoxMenu(ResourceManager* resourceManager, sf::Vector2f positionBtnOne, sf::Vector2f positionBtnTwo) :
button_yes(positionBtnOne, resourceManager->getTexture("Graphics/Menu/yes.png")),
button_no(positionBtnTwo, resourceManager->getTexture("Graphics/Menu/no.png"))
{
    items.push_back(&button_yes);
    items.push_back(&button_no);
}
