#ifndef LEVELEDITORMENU_HPP_INCLUDED
#define LEVELEDITORMENU_HPP_INCLUDED

#include "menu.hpp"
#include "button.hpp"
#include "gamestate.hpp"
#include "levelselectionmenu.hpp"
#include "collapsablebutton.hpp"

class LevelEditorMenu : public Menu
{
    public:
        LevelEditorMenu(ResourceManager* resourceManager);

        Button button_test;
        Button button_save;
        CollapsableButton button_tiles;
        Button button_toggleGrid;
        Button button_clear;

        //! Buttons for button_tiles
        Button button_tiles_childs[BUTTONT_TILES_CHILDS_SIZE];
};

#endif // LEVELEDITORMENU_HPP_INCLUDED
