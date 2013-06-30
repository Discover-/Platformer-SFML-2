#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "menuitem.hpp"

///\brief Button class for menu
class Button : public MenuItem, public sf::Sprite
{
    public:
        ///\brief Default constructor taking no argument
        Button();

        ///Callback is the function that is called when the button is activated(clicked)
        ///Position is, of course, the position of the button
        ///\note If the function required to call is a non-static class member, use the other constructor instead
        Button(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(Button*) = nullptr);

        ///\brief Constructor with callback for non-static member functions of a class
        ///Basically, a static redirect-function should be given as _callback, which converts classPointer into a pointer of its own type, so the non-static function can be called(see example in MainMenu(mainmenu.hpp))
        Button(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(void*, Button*), void* _classPointer);

        ///\brief Set the callback for global function or static member function
        void setCallback(void (*_callback)(Button*));

        ///\brief Set the callback for non-static member function
        void setCallback(void (*_callback)(void*, Button*), void* _classPointer);

        ///\brief Set the callback for non-static member function
        void setCallback(void (*_callback)(void*, Button*), void* _classPointer, std::string stringParam);

        ///\brief Check the given event.
        ///Returns true if handled
        bool handle_event(sf::Event _event);

        ///\brief Draw the button on target with states
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    protected:
        ///Callback function, called when the button is activated, and a pointer to the activated button is given
        void (*callback)(Button*);
        ///Callback function for non-static member functions, some tricks are needed
        ///Basically, a static redirect-function is given at construct, which converts classPointer into a pointer of its own type, so the non-static function can be called(see example in MainMenu(mainmenu.hpp))
        void (*memberCallback)(void*, Button*);
        void (*memberCallbackStringParam)(void*, Button*, std::string);
        void* classPointer;
        std::string stringParam;
};

#endif // BUTTON_HPP_INCLUDED
