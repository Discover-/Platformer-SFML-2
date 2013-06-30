#ifndef LEVELEDITORMENU_HPP_INCLUDED
#define LEVELEDITORMENU_HPP_INCLUDED

#include <string>

#include "menu.hpp"
#include "button.hpp"
#include "gamestate.hpp"
#include "levelselectionmenu.hpp"
#include "collapsablebutton.hpp"

///\brief Main menu class.
///See Menu(menu.hpp) for details
///The callback functions for the buttons have to be set if you want to use them
class LevelEditorMenu : public Menu
{
    public:
        ///\brief Default constructor
        LevelEditorMenu();

        ///\brief Constructor taking a pointer to a ResourceManager as argument
        ///Loads the default textures for the buttons and sets them
        LevelEditorMenu(ResourceManager* resourceManager);

        Button button_save;
        CollapsableButton button_tiles;
        Button button_toggleGrid;
};

#endif // LEVELEDITORMENU_HPP_INCLUDED
