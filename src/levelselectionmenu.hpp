#ifndef LEVELSELECTIONMENU_HPP_INCLUDED
#define LEVELSELECTIONMENU_HPP_INCLUDED

#include "menu.hpp"
#include "button.hpp"
#include "resourcemanager.hpp"

///!TODO: Let it create buttons for each level and load the textures for it etc., these functions are just placeholders to show how it could be implemented, without dynamic button creation

///\brief Menu for selecting a level.
///See Menu(menu.hpp) for details
///The callback functions for the buttons have to be set if you want to use them
class LevelSelectionMenu : public Menu
{
    public:
        ///\brief Default constructor
        LevelSelectionMenu();

        ///\brief Constructor taking a pointer to a ResourceManager as argument
        ///Loads the default textures for the buttons and sets them
        LevelSelectionMenu(ResourceManager* resourceManager);

        //The items, can and probably have to be edited by the owner of the LevelSelectionMenu(callbacks, anyone?)
        Button button_backToMenu;
        Button button_level1;
        Button button_level2;
        Button button_level3;
};

#endif // LEVELSELECTIONMENU_HPP_INCLUDED
