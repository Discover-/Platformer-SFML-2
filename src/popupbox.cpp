#include <iostream>

#include "popupbox.hpp"
#include "popupboxmenu.hpp"

PopUpBox::PopUpBox(sf::RenderWindow* renderWindow, StateManager* manager, std::string _popUpBoxMessage, sf::Vector2f position) : m_manager(manager), m_window(renderWindow)
{
    initialPosition = position;

    popUpBoxSelectBar.setOutlineColor(sf::Color::Black);
    popUpBoxSelectBar.setOutlineThickness(2.0f);
    popUpBoxSelectBar.setFillColor(sf::Color::Red);
    popUpBoxSelectBar.setSize(sf::Vector2f(300.0f, 25.0f));

    popUpBoxBackground.setOutlineColor(sf::Color::Black);
    popUpBoxBackground.setOutlineThickness(2.0f);
    popUpBoxBackground.setFillColor(sf::Color::White);
    popUpBoxBackground.setSize(sf::Vector2f(300.0f, 100.0f));

    popUpBoxMessage.setString(_popUpBoxMessage);
    popUpBoxMessage.setColor(sf::Color::Black);
    popUpBoxMessage.setFont(m_manager->resourceManager.getFont("Fonts/arial.ttf"));

    m_popUpBoxMenu = new PopUpBoxMenu(&m_manager->resourceManager);
    m_popUpBoxMenu->button_close.setCallback(&closeBox, this);
    m_popUpBoxMenu->button_yes.setCallback(&yes, this);
    m_popUpBoxMenu->button_no.setCallback(&no, this);

    m_pressedCloseBox = false;
    m_pressedYes = false;
    m_pressedNo = false;

    selectedPopUpBox = false;
    distSelectedBox = sf::Vector2f(0.0f, 0.0f);

    resetPositions();
}

PopUpBox::~PopUpBox()
{
    delete m_popUpBoxMenu;
}

void PopUpBox::resetPositions()
{
    popUpBoxSelectBar.setPosition(initialPosition);
    popUpBoxBackground.setPosition(initialPosition.x, initialPosition.y + 25.0f);
    popUpBoxMessage.setPosition(initialPosition.x, initialPosition.y + 25.0f);
    m_popUpBoxMenu->button_close.setPosition(initialPosition.x + 280.0f, initialPosition.y + 5.0f);
    m_popUpBoxMenu->button_yes.setPosition(initialPosition.x + 75.0f, initialPosition.y + 50.0f + 25.0f);
    m_popUpBoxMenu->button_no.setPosition(initialPosition.x + 175.0f, initialPosition.y + 50.0f + 25.0f);
    popUpBoxMessage.setPosition(initialPosition.x, initialPosition.y + 25.0f + 10.0f);

    //! Re-size the image till it fits exactly. Temporarily solution, we'll eventually have to add linebreaks, but oh well. :)
    while (popUpBoxMessage.getGlobalBounds().width > popUpBoxBackground.getGlobalBounds().width)
        popUpBoxMessage.setScale(popUpBoxMessage.getScale().x - 0.01f, popUpBoxMessage.getScale().y - 0.01f);
}

void PopUpBox::handle_events()
{
    sf::Event _event;

    while (m_window->pollEvent(_event))
    {
        m_popUpBoxMenu->handle_event(_event);

        switch (_event.type)
        {
            case sf::Event::MouseButtonPressed:
            {
                if (_event.mouseButton.button != sf::Mouse::Left)
                    break;

                if (!selectedPopUpBox && _event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    if (_event.mouseButton.x > popUpBoxSelectBar.getPosition().x && _event.mouseButton.x < popUpBoxSelectBar.getPosition().x + popUpBoxSelectBar.getGlobalBounds().width && _event.mouseButton.y > popUpBoxSelectBar.getPosition().y && _event.mouseButton.y < popUpBoxSelectBar.getPosition().y + popUpBoxSelectBar.getGlobalBounds().height)
                    {
                        selectedPopUpBox = true;
                        float distX = GetDistanceXorY(popUpBoxSelectBar.getPosition().x, float(_event.mouseButton.x));
                        float distY = GetDistanceXorY(popUpBoxSelectBar.getPosition().y, float(_event.mouseButton.y));
                        distSelectedBox = sf::Vector2f(distX, distY);
                        std::cout << "SELECTED!" << std::endl;
                    }
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                if (_event.mouseButton.button != sf::Mouse::Left)
                    break;

                if (selectedPopUpBox)
                {
                    selectedPopUpBox = false;
                    distSelectedBox = sf::Vector2f(0.0f, 0.0f);
                }
                break;
            }
            default:
                break;
        }
    }

    if (selectedPopUpBox)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

        if (!(mousePos.x > 1000 || mousePos.y > 600 || mousePos.x < 0 || mousePos.y < 0))
        {
            popUpBoxSelectBar.setPosition(float(mousePos.x - distSelectedBox.x), float(mousePos.y - distSelectedBox.y));
            popUpBoxBackground.setPosition(popUpBoxSelectBar.getPosition().x, popUpBoxSelectBar.getPosition().y + 25.0f);
            popUpBoxMessage.setPosition(popUpBoxSelectBar.getPosition().x, popUpBoxSelectBar.getPosition().y + 25.0f + 10.0f);
            m_popUpBoxMenu->button_close.setPosition(sf::Vector2f(popUpBoxSelectBar.getPosition().x + 280.0f, popUpBoxSelectBar.getPosition().y + 5.0f));
            m_popUpBoxMenu->button_yes.setPosition(sf::Vector2f(popUpBoxSelectBar.getPosition().x + 75.0f, popUpBoxSelectBar.getPosition().y + 50.0f + 25.0f));
            m_popUpBoxMenu->button_no.setPosition(sf::Vector2f(popUpBoxSelectBar.getPosition().x + 175.0f, popUpBoxSelectBar.getPosition().y + 50.0f + 25.0f));
        }
    }
}

void PopUpBox::logic(double passed, double deltaTime)
{

}

void PopUpBox::render(double alpha)
{
    //m_window->clear();
    m_window->draw(popUpBoxBackground);
    m_window->draw(popUpBoxSelectBar);
    m_window->draw(popUpBoxMessage);
    m_window->draw(*m_popUpBoxMenu);
    //m_window->display();
}

void PopUpBox::yes(void* inst, Button* button)
{
    ((PopUpBox*)inst)->m_pressedYes = true;
}

void PopUpBox::no(void* inst, Button* button)
{
    ((PopUpBox*)inst)->m_pressedNo = true;
}

void PopUpBox::closeBox(void* inst, Button* button)
{
    ((PopUpBox*)inst)->m_pressedCloseBox = true;
    ((PopUpBox*)inst)->resetPositions();
}
