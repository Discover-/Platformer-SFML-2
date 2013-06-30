#ifndef MAINMENUSTATE_HPP_INCLUDED
#define MAINMENUSTATE_HPP_INCLUDED

#include "mainmenu.hpp"
#include "button.hpp"
#include "gamestate.hpp"
#include "levelselectionmenu.hpp"

///\brief Main menu state.
///See GameState(gamestate.hpp) for more details
class MainMenuState : public GameState
{
    public:
        MainMenuState(sf::RenderWindow* renderWindow, StateManager* manager);

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha);

        StateManager* m_manager;

    private:
        sf::RenderWindow* m_window;

        ///Main menu
        //Callback functions for the menuitems
        static void play(void* inst, Button* button);
        static void options(void* inst, Button* button);
        static void levelEditor(void* inst, Button* button);
        static void exit(void* inst, Button* button);

        //The menu
        MainMenu m_mainMenu;

        ///LevelSelection menu
        //Callback functions
        static void backToMain(void* inst, Button* button);
        static void level1(void* inst, Button* button);

        //The menu
        LevelSelectionMenu m_levelSelectionMenu;

        ///\brief The current submenu
        ///This is the menu that will be drawn and which will check for events
        Menu* currentSubMenu;
};


#endif // MAINMENUSTATE_HPP_INCLUDED
