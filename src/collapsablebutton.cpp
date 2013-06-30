#include "collapsablebutton.hpp"

CollapsableButton::CollapsableButton(): callback(nullptr), memberCallback(nullptr), classPointer(nullptr)
{

}

CollapsableButton::CollapsableButton(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(CollapsableButton*) /* = nullptr */, bool _collapsed /* = true */)
:collapsed(_collapsed),
callback(_callback)
{
    setPosition(position);
    setTexture(_texture, true);
}

CollapsableButton::CollapsableButton(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(void*, CollapsableButton*), void* _classPointer, bool _collapsed /* = true */) : collapsed(_collapsed), callback(nullptr), memberCallback(_callback), classPointer(_classPointer)
{
    setPosition(position);
    setTexture(_texture, true);
}

void CollapsableButton::setCallback(void (*_callback)(CollapsableButton*))
{
    callback = _callback;
    memberCallback = nullptr;
    classPointer = nullptr;
}

void CollapsableButton::setCallback(void (*_callback)(void*, CollapsableButton*), void* _classPointer)
{
    memberCallback = _callback;
    classPointer = _classPointer;
    callback = nullptr;
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
                    else if (memberCallback != nullptr)
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
            break;

        default:
            break;
    }

    return handled;
}

void CollapsableButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (!collapsed)
        for (MenuItem* it : items)
            target.draw(*it, states);

    //Draw the collapsablebutton itself, I know it's a little hacky
    if (sf::Texture const* texture = getTexture())
    {
        states.transform *= getTransform();
        states.texture = texture;
        sf::Vertex vertices[4];
        sf::FloatRect bounds = getLocalBounds();
        vertices[0].position = sf::Vector2f(0, 0);
        vertices[1].position = sf::Vector2f(0, bounds.height);
        vertices[2].position = sf::Vector2f(bounds.width, bounds.height);
        vertices[3].position = sf::Vector2f(bounds.width, 0);

        float left   = static_cast<float>(getTextureRect().left);
        float right  = left + getTextureRect().width;
        float top    = static_cast<float>(getTextureRect().top);
        float bottom = top + getTextureRect().height;

        vertices[0].texCoords = sf::Vector2f(left, top);
        vertices[1].texCoords = sf::Vector2f(left, bottom);
        vertices[2].texCoords = sf::Vector2f(right, bottom);
        vertices[3].texCoords = sf::Vector2f(right, top);

        target.draw(vertices, 4, sf::Quads, states);
    }
}
