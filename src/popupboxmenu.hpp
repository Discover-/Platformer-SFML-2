#ifndef POPUPBOXMENU_HPP_INCLUDED
#define POPUPBOXMENU_HPP_INCLUDED

#include "menu.hpp"
#include "button.hpp"
#include "resourcemanager.hpp"

class PopUpBoxMenu : public Menu
{
    public:
        PopUpBoxMenu();
        PopUpBoxMenu(ResourceManager* resourceManager);

        Button button_close;
        Button button_yes;
        Button button_no;
};

#endif // POPUPBOXMENU_HPP_INCLUDED
