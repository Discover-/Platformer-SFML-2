#include <string>

#include "collapsablebutton.hpp"

CollapsableButton::CollapsableButton()
:collapsed(true)
{

}

CollapsableButton::CollapsableButton(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(CollapsableButton*, sf::Event&) /* = nullptr */, bool _collapsed /* = true */)
:collapsed(_collapsed)
{
    callbacks.MouseButtonReleased.set(_callback);
    setPosition(position);
    setTexture(_texture, true);
}

CollapsableButton::CollapsableButton(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(void*, CollapsableButton*, sf::Event&), void* _classPointer, bool _collapsed /* = true */)
:collapsed(_collapsed)
{
    callbacks.MouseButtonReleased.set(_callback, _classPointer);
    setPosition(position);
    setTexture(_texture, true);
}

bool CollapsableButton::handle_event(sf::Event _event)
{
    if (_event.type == sf::Event::EventType::MouseMoved)
    {
        //Check which items are currently focussed
        for (auto it : items)
        {
            if (it->isFocussed(sf::Vector2i(_event.mouseMove.x, _event.mouseMove.y)))
                focussedItems.push_back(it);
        }
    }

    bool handled = false;

    //Check the event on all the items
    for (auto it = focussedItems.rbegin(); it != focussedItems.rend(); ++it)
    {
        if ((*it)->handle_event(_event) == true)
        {
            handled = true;

            //The event is handled already, so we can move on
            break;
        }
    }

    //If the event still isn't handled, see if the collapsabe button itself can handle it
    if (!handled)
    {
        switch(_event.type)
        {
            case sf::Event::EventType::TextEntered:
                handled = callbacks.TextEntered(this, _event);
                break;

            case sf::Event::EventType::KeyPressed:
                handled = callbacks.KeyPressed(this, _event);
                break;

            case sf::Event::EventType::KeyReleased:
                handled = callbacks.KeyReleased(this, _event);
                break;

            case sf::Event::EventType::MouseWheelMoved:
                handled = callbacks.MouseWheelMoved(this, _event);
                break;

            case sf::Event::EventType::MouseButtonPressed:
                handled = callbacks.MouseButtonPressed(this, _event);
                break;

            case sf::Event::EventType::MouseButtonReleased:
                handled = callbacks.MouseButtonReleased(this, _event);
                if (handled)
                    collapsed = !collapsed; //Collapse or expand the button
                break;

            case sf::Event::EventType::MouseMoved:
                handled = callbacks.MouseMoved(this, _event);
                break;

            case sf::Event::EventType::JoystickButtonPressed:
                handled = callbacks.JoystickButtonPressed(this, _event);
                break;

            case sf::Event::EventType::JoystickButtonReleased:
                handled = callbacks.JoystickButtonReleased(this, _event);
                break;

            case sf::Event::EventType::JoystickMoved:
                handled = callbacks.JoystickMoved(this, _event);
                break;

            case sf::Event::EventType::JoystickConnected:
                handled = callbacks.JoystickConnected(this, _event);
                break;

            case sf::Event::EventType::JoystickDisconnected:
                handled = callbacks.JoystickDisconnected(this, _event);
                break;

            default:
                break;
        }
    }

    return handled;
}

void CollapsableButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (collapsed)
        for (MenuItem* itr : items)
            target.draw(*itr, states);

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

bool CollapsableButton::isFocussed(sf::Vector2i mousePos)
{
    if ( (mousePos.x > this->getPosition().x && mousePos.x <  this->getPosition().x + this->getGlobalBounds().width) && (mousePos.y > this->getPosition().y && mousePos.y < this->getPosition().y + this->getGlobalBounds().height) )
        return true; //The cursor is in the CollapsableButton itself

    for (auto it : items)
        if (it->isFocussed(mousePos))
            return true; //One of the child items is focussed, so we want to get events

    return false; //the cursor isn't in the button or child items, so we call it unfocussed.
}
