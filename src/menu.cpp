#include "menu.hpp"

Menu::~Menu()
{
    //for (std::list<MenuItem*>::iterator itr = items.begin(); itr != items.end(); ++itr)
    //    delete *itr;
}

bool Menu::handle_event(sf::Event _event)
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

    //If the event still isn't handled, see if the menu itself can handle it
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

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Draw all the items to target
    for (MenuItem* it : items)
        target.draw(*it, states);
}
