#include "gameminimenu.hpp"

GameMiniMenu::GameMiniMenu(sf::Vector2f buttonPositions[3])
{
    button_resume.setPosition(buttonPositions[0]);
    items.push_back(&button_resume);

    button_backToMenu.setPosition(buttonPositions[1]);
    items.push_back(&button_backToMenu);

    button_exit.setPosition(buttonPositions[2]);
    items.push_back(&button_exit);
}

GameMiniMenu::GameMiniMenu(ResourceManager* resourceManager, sf::Vector2f buttonPositions[3]) :
button_resume(buttonPositions[0], resourceManager->getTexture("Graphics/Menu/resume.png")),
button_backToMenu(buttonPositions[1], resourceManager->getTexture("Graphics/Menu/back_to_menu.png")),
button_exit(buttonPositions[2], resourceManager->getTexture("Graphics/Menu/exit.png"))
{
    items.push_back(&button_resume);
    items.push_back(&button_backToMenu);
    items.push_back(&button_exit);
}
