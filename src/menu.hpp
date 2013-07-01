#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "menuitem.hpp"
#include <list>

///A menu which can manage MenuItems
class Menu : public sf::Drawable
{
    public:
        ~Menu();

        ///\brief Check the events on the items
        ///Returns true if one of the items could handle it
        bool handle_event(sf::Event _event);
        ///\brief Draw the buttons on the target
        void draw (sf::RenderTarget &target, sf::RenderStates states) const;

        ///\brief The items
        std::list<MenuItem*> items;
};

#endif // MENU_HPP_INCLUDED
