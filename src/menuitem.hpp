#ifndef MENUITEM_HPP_INCLUDED
#define MENUITEM_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>

///! Base class for all child items of Menu (menu.hpp)
class MenuItem : public sf::Drawable
{
    public:
        ///\brief Checks the given event on the item
        ///Returns true if the event is handled
        virtual bool handle_event(sf::Event _event) = 0;

        ///\brief Draws the item on target
        virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const = 0;

        ///\brief Check if the item is focussed. The position of the mouse cursor is given.
        ///\note Only focussed items get to check events through handle_event
        virtual bool isFocussed(sf::Vector2i mousePos) = 0;
};

#endif // MENUITEM_HPP_INCLUDED
