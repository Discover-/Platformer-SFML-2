#include "menu.hpp"

bool Menu::handle_event(sf::Event event)
{
    bool handled = false;
    //Check the event on all the items
    for (MenuItem* it : items)
    {
        if (it->handle_event(event) == true)
            if (!handled)
                handled = true;
    }
    return handled;
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Draw all the items to target
    for (MenuItem* it : items)
    {
        target.draw(*it);
    }
}
