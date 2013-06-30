#include "button.hpp"

Button::Button(sf::Vector2f position, sf::Texture texture, void (*_callback)(Button*) /* = nullptr */)
:callback(_callback)
{
    this->setPosition(position);
    this->setTexture(texture);
}

bool Button::handle_event(sf::Event event)
{
    bool handled = false;
    switch(event.type)
    {
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                //Now check if the pointer was in the button
                if ( event.mouseButton.x > this->getPosition().x && event.mouseButton.x < this->getPosition().x + this->getGlobalBounds().width && event.mouseButton.y > this->getPosition().y && event.mouseButton.y < this->getPosition().y + this->getGlobalBounds().height)
                {
                    //The button was clicked. Now call it's callback function
                    callback(this);
                }
            }
    }
    return handled;
}
