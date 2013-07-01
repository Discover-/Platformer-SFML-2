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

    button_clear.setPosition(sf::Vector2f(550.0f, 20.0f));
    items.push_back(&button_clear);
}

LevelEditorMenu::LevelEditorMenu(ResourceManager* resourceManager) :
button_save(sf::Vector2f(20.0f, 20.0f), resourceManager->getTexture("Graphics/Menu/save.png")),
button_tiles(sf::Vector2f(170.0f, 20.0f), resourceManager->getTexture("Graphics/Menu/tiles.png")),
button_toggleGrid(sf::Vector2f(320.0f, 20.0f), resourceManager->getTexture("Graphics/Menu/toggle_grid.png")),
button_clear(sf::Vector2f(550.0f, 20.0f), resourceManager->getTexture("Graphics/Menu/clear.png")),

//Buttons for button_tiles
button_tiles_block1(sf::Vector2f(20.0f, 100.0f), resourceManager->getTexture("Graphics/Menu/block1.png")),
button_tiles_block2(sf::Vector2f(90.0f, 100.0f), resourceManager->getTexture("Graphics/Menu/block2.png")),
button_tiles_block3(sf::Vector2f(160.0f, 100.0f), resourceManager->getTexture("Graphics/Menu/block3.png")),
button_tiles_collisionPointer(sf::Vector2f(320.0f, 115.0f), resourceManager->getTexture("Graphics/Menu/collision_pointer.png"), nullptr, false)
{
    items.push_back(&button_save);
    items.push_back(&button_tiles);
    items.push_back(&button_toggleGrid);
    items.push_back(&button_clear);

    button_tiles.items.push_back(&button_tiles_block1);
    button_tiles.items.push_back(&button_tiles_block2);
    button_tiles.items.push_back(&button_tiles_block3);
    button_tiles.items.push_back(&button_tiles_collisionPointer);
}
