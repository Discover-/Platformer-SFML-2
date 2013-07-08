#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "menuitem.hpp"
#include "callback.hpp"

///\brief Button class for menu
class Button : public MenuItem, public sf::Sprite
{
    public:
        ///\brief Default constructor taking no argument
        Button();

        ///\brief Constructor setting the position, texture and MouseButtonReleased callback for global or static member functions
        ///\note If the MouseButtonReleased callback function required is a non-static class member, use the other constructor instead
        Button(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(Button*, sf::Event&) = nullptr);

        ///\brief Constructor setting the position, texture and the MouseButtonReleased callback for non-static member functions
        ///Basically, a static redirect-function should be given as _callback, which converts classPointer into a pointer of its own type, so the non-static function can be called(see example in MainMenu(mainmenu.hpp))
        Button(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(void*, Button*, sf::Event&), void* _classPointer);

        ///\brief Check the given event.
        ///Returns true if handled
        bool handle_event(sf::Event _event);

        ///\brief Draw the button on target with states
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        ///\brief Check if the item is focussed. The position of the mouse cursor is given.
        ///\note Only focussed items get to check events through handle_event
        bool isFocussed(sf::Vector2i mousePos);

        ///\brief Callback system
        ///\note See callback.hpp for more details
        CallbackSystem<Button> callbacks;
};

#endif // BUTTON_HPP_INCLUDED
