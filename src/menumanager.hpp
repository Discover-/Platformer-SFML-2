#pragma once

#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "gamestate.hpp"

enum MenuState
{
    MENU_STATE_NONE             = 0,
    MENU_STATE_MAIN             = 1,
    MENU_STATE_LEVEL_SELECTION  = 2,
    MENU_STATE_OPTIONS          = 3,
    MENU_STATE_LEVEL_EDITOR     = 4,
};

class MenuButton;

class MenuManager : public GameState
{
    public:
        MenuManager(sf::RenderWindow* renderWindow, StateManager* manager);

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha);

        void LoadMenus();
        void MouseButtonPressed(sf::Vector2i mousePos);

        std::map<MenuState, std::vector<MenuButton*> >& GetMenus() { return menus; }
        std::vector<MenuButton*>& GetMenuButtons(MenuState menuState) { return menus[menuState]; }

    private:
        StateManager* m_manager;
        sf::RenderWindow* m_window;

    private:
        MenuState currMenuState, nextMenuState, prevMenuState;
        std::map<MenuState /* menuState */, std::vector<MenuButton*> /* buttons */ > menus;
};
