#include "menu.hpp"

bool Menu::handle_event(sf::Event event)
{
    bool handled = false;
    for (Button* it : buttons)
    {
        if (it->handle_event(event) == true)
            if (!handled)
                handled = true;
    }
    return handled;
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Draw all the buttons to target
    for (Button* it : buttons)
    {
        target.draw(*it);
    }
}
