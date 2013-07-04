#include <sstream>

#include "leveleditormenu.hpp"
#include "leveleditorstate.hpp"

LevelEditorMenu::LevelEditorMenu(ResourceManager* resourceManager) :
button_test(sf::Vector2f(10.0f, 10.0f), resourceManager->getTexture("Graphics/Menu/test.png")),
button_save(sf::Vector2f(202.0f, 10.0f), resourceManager->getTexture("Graphics/Menu/save.png")),
button_tiles(sf::Vector2f(394.0f, 10.0f), resourceManager->getTexture("Graphics/Menu/tiles.png")),
button_clear(sf::Vector2f(202.0f, 45.0f), resourceManager->getTexture("Graphics/Menu/clear.png")),
button_toggleGrid(sf::Vector2f(10.0f, 45.0f), resourceManager->getTexture("Graphics/Menu/toggle_grid.png")),
button_toggleCollisionLines(sf::Vector2f(394.0f, 45.0f), resourceManager->getTexture("Graphics/Menu/toggle_collision_lines.png"))
{
    items.push_back(&button_save);
    items.push_back(&button_test);
    items.push_back(&button_tiles);
    items.push_back(&button_toggleGrid);
    items.push_back(&button_clear);
    items.push_back(&button_toggleCollisionLines);

    //! Buttons for button_tiles
    float blockPosX = 10.0f, blockPosY = 80.0f;

    for (int i = 0; i < BUTTONT_TILES_CHILDS_SIZE - 1; ++i) //! First 3 buttons are blocks
    {
        std::stringstream ss; ss << i + 1;
        button_tiles_childs[i] = Button(sf::Vector2f(blockPosX, blockPosY), resourceManager->getTexture("Graphics/Menu/block" + ss.str() + ".png"));
        blockPosX += 60.0f;
    }

    button_tiles_childs[3] = Button(sf::Vector2f(190.0f, 95.0f), resourceManager->getTexture("Graphics/Menu/collision_pointer.png"), nullptr, false);

    for (int i = 0; i < BUTTONT_TILES_CHILDS_SIZE; ++i)
        button_tiles.items.push_back(&button_tiles_childs[i]);
}
