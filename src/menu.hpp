#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "button.hpp"

///Base class for all menus
class Menu : public sf::Drawable
{
    public:
        ///\brief Check the events on the buttons
        ///Returns true if one of the buttons could handle it
        bool handle_event(sf::Event event);
        ///\brief Draw the buttons on the target
        void draw (sf::RenderTarget &target, sf::RenderStates states) const;

        ///\brief The buttons
        std::vector<Button*> buttons;
};

#endif // MENU_HPP_INCLUDED
