#include "leveleditormenu.hpp"
#include "leveleditorstate.hpp"

LevelEditorMenu::LevelEditorMenu(ResourceManager* resourceManager) :
button_save(sf::Vector2f(10.0f, 10.0f), resourceManager->getTexture("Graphics/Menu/save.png")),
button_tiles(sf::Vector2f(202.0f, 10.0f), resourceManager->getTexture("Graphics/Menu/tiles.png")),
button_clear(sf::Vector2f(394.0f, 10.0f), resourceManager->getTexture("Graphics/Menu/clear.png")),
button_toggleGrid(sf::Vector2f(10.0f, 45.0f), resourceManager->getTexture("Graphics/Menu/toggle_grid.png"))
{
    items.push_back(&button_save);
    items.push_back(&button_tiles);
    items.push_back(&button_toggleGrid);
    items.push_back(&button_clear);

    //Buttons for button_tiles
    button_tiles_childs[0] = Button(sf::Vector2f(10.0f, 80.0f), resourceManager->getTexture("Graphics/Menu/block1.png"));
    button_tiles_childs[1] = Button(sf::Vector2f(70.0f, 80.0f), resourceManager->getTexture("Graphics/Menu/block2.png"));
    button_tiles_childs[2] = Button(sf::Vector2f(130.0f, 80.0f), resourceManager->getTexture("Graphics/Menu/block3.png"));
    button_tiles_childs[3] = Button(sf::Vector2f(190.0f, 95.0f), resourceManager->getTexture("Graphics/Menu/collision_pointer.png"), nullptr, false);

    for (int i = 0; i < BUTTONT_TILES_CHILDS_SIZE; ++i)
        button_tiles.items.push_back(&button_tiles_childs[i]);
}
