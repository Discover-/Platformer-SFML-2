#ifndef COLLAPSABLEBUTTON_HPP_INCLUDED
#define COLLAPSABLEBUTTON_HPP_INCLUDED

#include "button.hpp"
#include <list>

///\brief Button with child items(dropdown-like)
class CollapsableButton : public MenuItem, sf::Sprite
{
    public:
        ///\brief Collapsable button class for menu
        ///When collapsed, the child items aren't being drawn and events are not checked against them
        ///When the Collapsable button is activated
        ///Callback function is called when the collapsable button is activated(clicked)
        ///Position is, of course, the position of the collapsable button
        ///The offset of the position of the child items IS NOT the position of the collapsable button, but the standard offset
        CollapsableButton(sf::Vector2f position, sf::Texture texture, void (*_callback)(CollapsableButton*) = nullptr, bool _collapsed = false);

        ///\brief Check the event on the button and on the child items if expanded(not collapsed).
        bool handle_event(sf::Event event);

        ///\brief Draw the button and child items if expanded(not collapsed) on target
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        ///\brief If false, the child items are visible and events are checked on them
        bool collapsed;

        ///\brief The child items, these are visible and events are checked on them only when collapsed=false
        std::list<MenuItem*> items;

        void (*callback)(CollapsableButton*);
};

#endif // COLLAPSABLEBUTTON_HPP_INCLUDED
