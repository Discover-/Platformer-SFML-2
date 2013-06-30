#ifndef COLLAPSABLEBUTTON_HPP_INCLUDED
#define COLLAPSABLEBUTTON_HPP_INCLUDED

#include "button.hpp"
#include <list>

///\brief Button with child items(dropdown-like)
///When collapsed, the child items aren't being drawn and events are not checked against them
///When the Collapsable button is activated
///Callback function is called when the collapsable button is activated(clicked)
///Position is, of course, the position of the collapsable button
///The offset of the position of the child items IS NOT the position of the collapsable button, but the standard offset
class CollapsableButton : public MenuItem, public sf::Sprite
{
    public:
        ///\brief Default constructor taking no argument
        CollapsableButton();

        ///Callback is the function that is called when the button is activated(clicked)
        ///Position is, of course, the position of the button
        ///\note If the function required to call is a non-static class member, use the other constructor instead
        CollapsableButton(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(CollapsableButton*) = nullptr, bool collapsed = true);

        ///\brief Constructor with callback for non-static member functions of a class
        ///Basically, a static redirect-function should be given as _callback, which converts classPointer into a pointer of its own type, so the non-static function can be called(see example in MainMenu(mainmenu.hpp))
        CollapsableButton(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(void*, CollapsableButton*), void* _classPointer, bool collapsed = true);

        ///\brief Set the callback for global function or static member function
        void setCallback(void (*_callback)(CollapsableButton*));

        ///\brief Set the callback for non-static member function
        void setCallback(void (*_callback)(void*, CollapsableButton*), void* _classPointer);

        ///\brief Check the event on the button and on the child items if expanded(not collapsed).
        bool handle_event(sf::Event _event);

        ///\brief Draw the button and child items if expanded(not collapsed) on target
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        ///\brief If false, the child items are visible and events are checked on them
        bool collapsed;

        ///\brief The child items, these are visible and events are checked on them only when collapsed=false
        std::list<MenuItem*> items;

    private:
        ///Callback function, called when the button is activated, and a pointer to the activated button is given
        void (*callback)(CollapsableButton*);
        ///Callback function for non-static member functions, some tricks are needed
        ///Basically, a static redirect-function is given at construct, which converts classPointer into a pointer of its own type, so the non-static function can be called(see example in MainMenu(mainmenu.hpp)
        void (*memberCallback)(void*, CollapsableButton*);
        void* classPointer;
};

#endif // COLLAPSABLEBUTTON_HPP_INCLUDED
