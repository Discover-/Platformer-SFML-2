#include "leveleditormenu.hpp"
#include "leveleditorstate.hpp"

LevelEditorMenu::LevelEditorMenu()
{
    button_save.setPosition(sf::Vector2f(10.0f, 10.0f));
    items.push_back(&button_save);

    button_tiles.setPosition(sf::Vector2f(120.0f, 10.0f));
    items.push_back(&button_tiles);

    button_clear.setPosition(sf::Vector2f(230.0f, 10.0f));
    items.push_back(&button_clear);

    button_toggleGrid.setPosition(sf::Vector2f(340.0f, 10.0f));
    items.push_back(&button_toggleGrid);

    button_tiles_block1.setPosition(sf::Vector2f(10.0f, 65.0f));
    button_tiles.items.push_back(&button_tiles_block1);

    button_tiles_block2.setPosition(sf::Vector2f(70.0f, 65.0f));
    button_tiles.items.push_back(&button_tiles_block2);

    button_tiles_block3.setPosition(sf::Vector2f(130.0f, 65.0f));
    button_tiles.items.push_back(&button_tiles_block3);

    button_tiles_collisionPointer.setPosition(sf::Vector2f(190.0f, 80.0f));
    button_tiles.items.push_back(&button_tiles_collisionPointer);
}

LevelEditorMenu::LevelEditorMenu(ResourceManager* resourceManager) :
button_save(sf::Vector2f(10.0f, 10.0f), resourceManager->getTexture("Graphics/Menu/save.png")),
button_tiles(sf::Vector2f(120.0f, 10.0f), resourceManager->getTexture("Graphics/Menu/tiles.png")),
button_clear(sf::Vector2f(230.0f, 10.0f), resourceManager->getTexture("Graphics/Menu/clear.png")),
button_toggleGrid(sf::Vector2f(340.0f, 10.0f), resourceManager->getTexture("Graphics/Menu/toggle_grid.png")),

//Buttons for button_tiles
button_tiles_block1(sf::Vector2f(10.0f, 65.0f), resourceManager->getTexture("Graphics/Menu/block1.png")),
button_tiles_block2(sf::Vector2f(70.0f, 65.0f), resourceManager->getTexture("Graphics/Menu/block2.png")),
button_tiles_block3(sf::Vector2f(130.0f, 65.0f), resourceManager->getTexture("Graphics/Menu/block3.png")),
button_tiles_collisionPointer(sf::Vector2f(190.0f, 80.0f), resourceManager->getTexture("Graphics/Menu/collision_pointer.png"), nullptr, false)
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
