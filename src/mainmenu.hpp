#ifndef MAINMENU_HPP_INCLUDED
#define MAINMENU_HPP_INCLUDED

#include "menu.hpp"
#include "button.hpp"
#include "gamestate.hpp"
#include "levelselectionmenu.hpp"

///\brief Main menu class.
///See Menu(menu.hpp) for details
///The callback functions for the buttons have to be set if you want to use them
class MainMenu : public Menu
{
    public:
        ///\brief Default constructor
        MainMenu();

        ///\brief Constructor taking a pointer to a ResourceManager as argument
        ///Loads the default textures for the buttons and sets them
        MainMenu(ResourceManager* resourceManager);

        //The items, can and probably have to be edited by the owner of the LevelSelectionMenu(callbacks, anyone?)
        Button button_play;
        Button button_options;
        Button button_levelEditor;
        Button button_exit;
};

#endif // MAINMENU_HPP_INCLUDED
