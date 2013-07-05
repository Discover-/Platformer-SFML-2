#ifndef POPUPBOX_HPP_INCLUDED
#define POPUPBOX_HPP_INCLUDED

#include <string>

#include "button.hpp"
#include "statemanager.hpp"
#include "popupboxmenu.hpp"

class PopUpBox
{
    public:
        PopUpBox(sf::RenderWindow* renderWindow, StateManager* manager, std::string _popUpBoxMessage, sf::Vector2f position);
        ~PopUpBox();

        bool handle_event(sf::Event& _event);
        void logic(double passed, double deltaTime);
        void render(double alpha);

        static void closeBox(void* inst, Button* button);
        static void yes(void* inst, Button* button);
        static void no(void* inst, Button* button);

        void setPosition(sf::Vector2f newPos);
        inline const sf::Vector2f& getPosition() const;
        void resetPositions();

        bool m_pressedYes, m_pressedNo, m_pressedCloseBox;

    private:
        StateManager* m_manager;
        sf::Text popUpBoxMessage;
        sf::RectangleShape popUpBoxBackground, popUpBoxSelectBar;
        sf::RenderWindow* m_window;
        PopUpBoxMenu m_popUpBoxMenu;

        sf::Vector2f initialPosition;
        sf::Vector2f m_prevPos; //Needed for interpolation, see gamestate.hpp for more details

        bool selectedPopUpBox;
        sf::Vector2f distSelectedBox;
};


#endif // POPUPBOX_HPP_INCLUDED
