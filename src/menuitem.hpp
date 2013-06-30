#ifndef MENUITEM_HPP_INCLUDED
#define MENUITEM_HPP_INCLUDED

#include <SFML/Graphics.hpp>

///Base class for all child items of Menu(menu.hpp)
class MenuItem : public sf::Drawable
{
    public:
        ///\brief Checks the given event on the item
        ///Returns true if the event is handled
        virtual bool handle_event(sf::Event event) = 0;

        ///\brief Draws the item on target
        virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const = 0;
};

#endif // MENUITEM_HPP_INCLUDED
