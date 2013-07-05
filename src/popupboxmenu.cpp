#include "popupboxmenu.hpp"

PopUpBoxMenu::PopUpBoxMenu(ResourceManager* resourceManager) :
button_close(sf::Vector2f(0.0f, 0.0f), resourceManager->getTexture("Graphics/Menu/close_box.png")),
button_yes(sf::Vector2f(0.0f, 0.0f), resourceManager->getTexture("Graphics/Menu/yes.png")),
button_no(sf::Vector2f(0.0f, 0.0f), resourceManager->getTexture("Graphics/Menu/no.png"))
{
    items.push_back(&button_close);
    items.push_back(&button_yes);
    items.push_back(&button_no);
}
