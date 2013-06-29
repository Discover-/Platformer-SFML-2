#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Button : public sf::Sprite
{
    public:
        ///\brief Button class for menu
        ///Callback is the function that is called when the button is activated(clicked)
        ///Position is, of course, the position of the button
        Button(sf::Vector2f position, sf::Texture texture, void (*callback)());

        bool handle_event(sf::Event event);

        ///Callback function, called when the button is activated
        void (*m_callback)();
};

#endif // BUTTON_HPP_INCLUDED
