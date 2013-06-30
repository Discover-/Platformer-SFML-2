#include "collapsablebutton.hpp"

CollapsableButton::CollapsableButton(sf::Vector2f position, sf::Texture texture, void (*_callback)(CollapsableButton*) /* = nullptr */, bool _collapsed /* = true */)
:collapsed(_collapsed),
callback(_callback)
{
    setPosition(position);
    setTexture(texture);
}

CollapsableButton::CollapsableButton(sf::Vector2f position, sf::Texture texture, void (*_callback)(void*, CollapsableButton*), void* _classPointer, bool _collapsed /* = true */) : collapsed(_collapsed), callback(nullptr), memberCallback(_callback), classPointer(_classPointer)
{
    setPosition(position);
    setTexture(texture);
}

bool CollapsableButton::handle_event(sf::Event _event)
{
    bool handled = false;

    //Check the event on all the child items, if collapsed
    if (collapsed)
        for (MenuItem* it : items)
            if (it->handle_event(_event) == true)
                if (!handled)
                    handled = true;

    //Check the event on the CollapsableButton
    switch (_event.type)
    {
        case sf::Event::MouseButtonReleased:
            if (_event.mouseButton.button == sf::Mouse::Button::Left)
            {
                //Now check if the pointer was in the button
                if (_event.mouseButton.x > getPosition().x && _event.mouseButton.x < getPosition().x + getGlobalBounds().width && _event.mouseButton.y > getPosition().y && _event.mouseButton.y < getPosition().y + getGlobalBounds().height)
                {
                    //The button was clicked. Now call it's callback function
                    if (classPointer == nullptr)
                    {
                        if (callback != nullptr)
                        {
                            //The callback function is a static member or global function
                            callback(this);
                        }
                    }
                    else
                    {
                        //The callback function is a non-static member function, some tricks are needed
                        memberCallback(classPointer, this);
                    }
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

void CollapsableButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (!collapsed)
        for (MenuItem* it : items)
            target.draw(*it, states);

    //Draw the collapsablebutton itself, I know it's a little hacky
    if (getTexture())
    {
        states.transform *= getTransform();
        states.texture = getTexture();
        sf::Vertex vertices[4];
        sf::FloatRect bounds = getLocalBounds();
        vertices[0].position = sf::Vector2f(0, 0);
        vertices[1].position = sf::Vector2f(0, bounds.height);
        vertices[2].position = sf::Vector2f(bounds.width, bounds.height);
        vertices[3].position = sf::Vector2f(bounds.width, 0);
        target.draw(vertices, 4, sf::Quads, states);
    }
}
