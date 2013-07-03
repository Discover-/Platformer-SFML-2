#include "levelselectionmenu.hpp"

LevelSelectionMenu::LevelSelectionMenu(ResourceManager* resourceManager) :
button_backToMenu(sf::Vector2f(300.0f, 0.0f), resourceManager->getTexture("Graphics/Menu/back.png")),
button_level1(sf::Vector2f(300.0f, 100.0f), resourceManager->getTexture("Graphics/Menu/level_1.png")),
button_level2(sf::Vector2f(300.0f, 200.0f), resourceManager->getTexture("Graphics/Menu/level_2.png")),
button_level3(sf::Vector2f(300.0f, 300.0f), resourceManager->getTexture("Graphics/Menu/level_3.png"))
{
    items.push_back(&button_backToMenu);
    items.push_back(&button_level1);
    items.push_back(&button_level2);
    items.push_back(&button_level3);
}
