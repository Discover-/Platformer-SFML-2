#include "leveleditormenu.hpp"
#include "leveleditorstate.hpp"

LevelEditorMenu::LevelEditorMenu()
{
    button_save.setPosition(sf::Vector2f(20.0f, 20.0f));
    items.push_back(&button_save);

    button_tiles.setPosition(sf::Vector2f(170.0f, 20.0f));
    items.push_back(&button_tiles);

    button_toggleGrid.setPosition(sf::Vector2f(320.0f, 20.0f));
    items.push_back(&button_toggleGrid);
}

LevelEditorMenu::LevelEditorMenu(ResourceManager* resourceManager) :
button_save(sf::Vector2f(20.0f, 20.0f), resourceManager->getTexture("Graphics/Menu/save.png")),
button_tiles(sf::Vector2f(170.0f, 20.0f), resourceManager->getTexture("Graphics/Menu/tiles.png")),
button_toggleGrid(sf::Vector2f(320.0f, 20.0f), resourceManager->getTexture("Graphics/Menu/enable_grid.png"))
{
    items.push_back(&button_save);
    items.push_back(&button_tiles);
    items.push_back(&button_toggleGrid);

    button_tiles.items.push_back(std::make_pair(new Button(sf::Vector2f(20.0f, 100.0f), resourceManager->getTexture("Graphics/Menu/block1.png"), ), "Graphics/Menu/block1.png"));
    button_tiles.items.push_back(std::make_pair(new Button(sf::Vector2f(120.0f, 100.0f), resourceManager->getTexture("Graphics/Menu/block2.png")), "Graphics/Menu/block2.png"));
    button_tiles.items.push_back(std::make_pair(new Button(sf::Vector2f(220.0f, 100.0f), resourceManager->getTexture("Graphics/Menu/block3.png")), "Graphics/Menu/block3.png"));
}
x