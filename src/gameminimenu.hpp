#ifndef GAMEMINIMENU_HPP_INCLUDED
#define GAMEMINIMENU_HPP_INCLUDED

#include "menu.hpp"
#include "button.hpp"
#include "gamestate.hpp"
#include "levelselectionmenu.hpp"

class GameMiniMenu : public Menu
{
    public:
        GameMiniMenu(sf::Vector2f buttonPositions[3]);
        GameMiniMenu(ResourceManager* resourceManager, sf::Vector2f buttonPositions[3]);

        Button button_resume;
        Button button_backToMenu;
        Button button_exit;
};

#endif // GAMEMINIMENU_HPP_INCLUDED
