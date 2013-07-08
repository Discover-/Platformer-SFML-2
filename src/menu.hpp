#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "menuitem.hpp"
#include <list>
#include "callback.hpp"

///A menu which can manage MenuItems
class Menu : public sf::Drawable
{
    public:
        ~Menu();

        ///\brief Check the events on the items
        ///Returns true if one of the items could handle it
        bool handle_event(sf::Event _event);
        ///\brief Draw the buttons on the target
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        ///\brief The items
        std::list<MenuItem*> items;

        ///\brief Currently focussed items.
        ///Only focussed items can handle events
        ///An item gets focussed if the mouse cursor is on top of it
        std::list<MenuItem*> focussedItems;

        ///\brief Callback system
        ///\note See callback.hpp for more details
        CallbackSystem<Menu> callbacks;
};

#endif // MENU_HPP_INCLUDED
