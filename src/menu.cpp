#include "menu.hpp"

bool Menu::handle_event(sf::Event _event)
{
    bool handled = false;
    //Check the event on all the items
    for (MenuItem* it : items)
        if (it->handle_event(_event) == true)
            if (!handled)
                handled = true;

    return handled;
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //Draw all the items to target
    for (MenuItem* it : items)
        target.draw(*it, states);
}
