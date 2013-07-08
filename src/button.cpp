#include "button.hpp"

Button::Button()
{

}

Button::Button(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(Button*, sf::Event&) /* = nullptr */)
{
    callbacks.MouseButtonReleased.set(_callback);
    setPosition(position);
    setTexture(_texture, true);
}

Button::Button(sf::Vector2f position, sf::Texture&  _texture, void (*_callback)(void*, Button*, sf::Event&), void* _classPointer)
{
    callbacks.MouseButtonReleased.set(_callback, _classPointer);
    setPosition(position);
    setTexture(_texture, true);
}

bool Button::handle_event(sf::Event _event)
{
    bool handled = false;

    //Call the callback function for the type of _event, if one exists.
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

    return handled;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Draw the button itself, I know it's a little hacky
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

bool Button::isFocussed(sf::Vector2i mousePos)
{
    if ( (mousePos.x > this->getPosition().x && mousePos.x <  this->getPosition().x + this->getGlobalBounds().width) && (mousePos.y > this->getPosition().y && mousePos.y < this->getPosition().y + this->getGlobalBounds().height) )
        return true; //The cursor is in the button, so we call the button focussed.
    return false; //the cursor isn't in the button, so we call it unfocussed.
}
