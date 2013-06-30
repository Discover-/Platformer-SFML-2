#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "menuitem.hpp"

class Button : public MenuItem, sf::Sprite
{
    public:
        ///\brief Button class for menu
        ///Callback is the function that is called when the button is activated(clicked)
        ///Position is, of course, the position of the button
        Button(sf::Vector2f position, sf::Texture texture, void (*_callback)(Button*) = nullptr);

        bool handle_event(sf::Event event);

        ///Callback function, called when the button is activated, and a pointer to the activated button is given
        void (*callback)(Button*);
};

#endif // BUTTON_HPP_INCLUDED
