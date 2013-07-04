#include <iostream>

#include "popupbox.hpp"
#include "popupboxmenu.hpp"

PopUpBox::PopUpBox(sf::RenderWindow* renderWindow, StateManager* manager, std::string _popUpBoxMessage, sf::Vector2f position) : m_manager(manager), m_window(renderWindow), m_popUpBoxMenu(&m_manager->resourceManager), m_prevPos(position)
{
    initialPosition = position;
    m_prevPos = position;

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

    m_popUpBoxMenu.button_close.setCallback(&closeBox, this);
    m_popUpBoxMenu.button_yes.setCallback(&yes, this);
    m_popUpBoxMenu.button_no.setCallback(&no, this);

    m_pressedCloseBox = false;
    m_pressedYes = false;
    m_pressedNo = false;

    selectedPopUpBox = false;
    distSelectedBox = sf::Vector2f(0.0f, 0.0f);

    resetPositions();
}

PopUpBox::~PopUpBox()
{

}

void PopUpBox::resetPositions()
{
    setPosition(initialPosition);
    //! Re-size the image till it fits exactly. Temporarily solution, we'll eventually have to add linebreaks, but oh well. :)
    while (popUpBoxMessage.getGlobalBounds().width + 5.0f > popUpBoxBackground.getGlobalBounds().width)
        popUpBoxMessage.setScale(popUpBoxMessage.getScale().x - 0.01f, popUpBoxMessage.getScale().y - 0.01f);
}

void PopUpBox::setPosition(sf::Vector2f newPos)
{
    m_prevPos = popUpBoxSelectBar.getPosition();
    popUpBoxSelectBar.setPosition(newPos);
    popUpBoxBackground.setPosition(newPos.x, newPos.y + 25.0f);
    popUpBoxMessage.setPosition(newPos.x, newPos.y + 25.0f);

    m_popUpBoxMenu.button_close.setPosition(newPos.x + 280.0f, newPos.y + 5.0f);
    m_popUpBoxMenu.button_yes.setPosition(newPos.x + 75.0f, newPos.y + 50.0f + 25.0f);
    m_popUpBoxMenu.button_no.setPosition(newPos.x + 175.0f, newPos.y + 50.0f + 25.0f);
    popUpBoxMessage.setPosition(newPos.x, newPos.y + 25.0f + 10.0f);
}

inline const sf::Vector2f& PopUpBox::getPosition() const
{
    return popUpBoxSelectBar.getPosition();
}

bool PopUpBox::handle_event(sf::Event& _event)
{

    //If the menu handled the event, the box doesn't have to handle it
    if (m_popUpBoxMenu.handle_event(_event))
        return true;

    bool handled = false;

    switch (_event.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            if (!selectedPopUpBox && _event.mouseButton.button == sf::Mouse::Button::Left)
            {
                if (_event.mouseButton.x > popUpBoxSelectBar.getPosition().x && _event.mouseButton.x < popUpBoxSelectBar.getPosition().x + popUpBoxSelectBar.getGlobalBounds().width && _event.mouseButton.y > popUpBoxSelectBar.getPosition().y && _event.mouseButton.y < popUpBoxSelectBar.getPosition().y + popUpBoxSelectBar.getGlobalBounds().height)
                {
                    selectedPopUpBox = true;
                    float distX = GetDistanceXorY(popUpBoxSelectBar.getPosition().x, float(_event.mouseButton.x));
                    float distY = GetDistanceXorY(popUpBoxSelectBar.getPosition().y, float(_event.mouseButton.y));
                    distSelectedBox = sf::Vector2f(distX, distY);
                    handled = true;
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
                handled = true;
            }
            break;
        }
        case sf::Event::MouseMoved:
        {
            if (selectedPopUpBox)
            {
                if (!(_event.mouseMove.x > m_window->getSize().x || _event.mouseMove.y > m_window->getSize().y || _event.mouseMove.x < 0 || _event.mouseMove.y < 0))
                setPosition(sf::Vector2f(float(_event.mouseMove.x - distSelectedBox.x), float(_event.mouseMove.y - distSelectedBox.y)));
            }
            break;
        }
        default:
            break;
        }

    /*if (selectedPopUpBox)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

        if (!(mousePos.x > 1000 || mousePos.y > 600 || mousePos.x < 0 || mousePos.y < 0))
        {
            setPosition(sf::Vector2f(float(mousePos.x - distSelectedBox.x), float(mousePos.y - distSelectedBox.y)));
        }
    }*/
    return handled;
}

void PopUpBox::logic(double passed, double deltaTime)
{

}

void PopUpBox::render(double alpha)
{
    //Interpolate the position, state = currentstate * alpha + previousstate * ( 1 - alpha )
    sf::Vector2f realPos = getPosition();
    setPosition(sf::Vector2f(realPos.x * alpha + m_prevPos.x * (1 - alpha), realPos.y * alpha + m_prevPos.y * (1 - alpha)));

    //Draw everything
    m_window->draw(popUpBoxBackground);
    m_window->draw(popUpBoxSelectBar);
    m_window->draw(popUpBoxMessage);
    m_window->draw(m_popUpBoxMenu);

    //Set the real position back
    setPosition(realPos);
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
