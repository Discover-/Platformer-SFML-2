#include "collapsablebutton.hpp"

CollapsableButton::CollapsableButton(sf::Vector2f position, sf::Texture texture, void (*_callback)(CollapsableButton*) /* = nullptr */, bool _collapsed /* = false */)
:collapsed(_collapsed),
callback(_callback)
{
    this->setPosition(position);
    this->setTexture(texture);
}

bool CollapsableButton::handle_event(sf::Event event)
{
    bool handled = false;
    //Check the event on all the child items, if collapsed
    if (collapsed)
    {
        for (MenuItem* it : items)
        {
            if (it->handle_event(event) == true)
                if (!handled)
                    handled = true;
        }
    }

    //Check the event on the CollapsableButton
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
                    //Also, expand or collapse
                    if (collapsed)
                        collapsed = false;
                    else
                        collapsed = true;

                    //Now the event is handled
                    if (!handled)
                        handled = true;
                }
            }
    }

    return handled;
}
