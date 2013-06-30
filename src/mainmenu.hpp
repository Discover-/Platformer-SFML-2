#ifndef MAINMENU_HPP_INCLUDED
#define MAINMENU_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "menu.hpp"
#include "button.hpp"
#include "gamestate.hpp"

///\brief Main menu class.
///See GameState(gamestate.hpp) for more details
class MainMenu : public GameState
{
    public:
        MainMenu(sf::RenderWindow* renderWindow, StateManager* manager);

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha);

        StateManager* m_manager;

    private:
        sf::RenderWindow* m_window;

        //Callback functions for the menuitems
        static void play(void* inst, Button* button);
        static void options(void* inst, Button* button);
        static void levelEditor(void* inst, Button* button);
        static void exit(void* inst, Button* button);

        //The menu and items
        Menu m_menu;
        Button m_button_play;
        Button m_button_options;
        Button m_button_levelEditor;
        Button m_button_exit;

};

#endif // MAINMENU_HPP_INCLUDED
