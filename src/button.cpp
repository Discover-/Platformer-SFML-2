#include "button.hpp"

Button::Button() :
callback(nullptr), memberCallback(nullptr), classPointer(nullptr)
{

}

Button::Button(sf::Vector2f position, sf::Texture& _texture, void (*_callback)(Button*) /* = nullptr */) :
callback(_callback), memberCallback(nullptr), classPointer(nullptr)
{
    setPosition(position);
    setTexture(_texture, true);
}

Button::Button(sf::Vector2f position, sf::Texture&  _texture, void (*_callback)(void*, Button*), void* _classPointer) :
callback(nullptr), memberCallback(_callback), classPointer(_classPointer)
{
    setPosition(position);
    setTexture(_texture, true);
}

void Button::setCallback(void (*_callback)(Button*))
{
    callback = _callback;
    memberCallback = nullptr;
    classPointer = nullptr;
}

void Button::setCallback(void (*_callback)(void*, Button*), void* _classPointer)
{
    memberCallback = _callback;
    classPointer = _classPointer;
    callback = nullptr;
}

bool Button::handle_event(sf::Event _event)
{
    bool handled = false;

    switch (_event.type)
    {
        case sf::Event::MouseButtonReleased:
        {
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

                    //Now the event is handled
                    if (!handled)
                        handled = true;
                }
            }
            break;
        }
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
