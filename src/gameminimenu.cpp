#include "gameminimenu.hpp"

GameMiniMenu::GameMiniMenu(ResourceManager* resourceManager, sf::Vector2f buttonPositions[3]) :
button_resume(buttonPositions[0], resourceManager->getTexture("Graphics/Menu/resume.png")),
button_backToMenu(buttonPositions[1], resourceManager->getTexture("Graphics/Menu/back_to_menu.png")),
button_exit(buttonPositions[2], resourceManager->getTexture("Graphics/Menu/exit.png"))
{
    items.push_back(&button_resume);
    items.push_back(&button_backToMenu);
    items.push_back(&button_exit);
}
