#include "popupbox.hpp"
#include "popupboxmenu.hpp"

PopUpBox::PopUpBox(sf::RenderWindow* renderWindow, StateManager* manager, std::string _popUpBoxMessage, sf::Vector2f position) : m_manager(manager), m_window(renderWindow)
{
    menuBackground.setOutlineColor(sf::Color::Black);
    menuBackground.setOutlineThickness(2.0f);
    menuBackground.setFillColor(sf::Color::White);
    menuBackground.setSize(sf::Vector2f(300.0f, 100.0f));
    menuBackground.setPosition(position);

    popUpBoxMessage.setString(_popUpBoxMessage);
    popUpBoxMessage.setColor(sf::Color::Black);
    popUpBoxMessage.setPosition(position);
    popUpBoxMessage.setPosition(popUpBoxMessage.getPosition().x - popUpBoxMessage.getGlobalBounds().width / 2.0f, popUpBoxMessage.getPosition().y - popUpBoxMessage.getGlobalBounds().height / 2.0f + 10.0f);
    popUpBoxMessage.setFont(m_manager->resourceManager.getFont("Fonts/arial.ttf"));

    //! Re-size the image till it fits exactly. Temporarily solution, we'll eventually have to add linebreaks, but oh well. :)
    while (popUpBoxMessage.getGlobalBounds().width > menuBackground.getGlobalBounds().width)
        popUpBoxMessage.setScale(popUpBoxMessage.getScale().x - 0.01f, popUpBoxMessage.getScale().y - 0.01f);

    m_popUpBoxMenu = new PopUpBoxMenu(&m_manager->resourceManager, sf::Vector2f(position.x + 75.0f, position.y + 50.0f), sf::Vector2f(position.x + 175.0f, position.y + 50.0f));
    m_popUpBoxMenu->button_yes.setCallback(&yes, this);
    m_popUpBoxMenu->button_no.setCallback(&no, this);

    m_pressedYes = false;
    m_pressedNo = false;
}

PopUpBox::~PopUpBox()
{
    delete m_popUpBoxMenu;
}

void PopUpBox::handle_events()
{
    sf::Event _event;

    while (m_window->pollEvent(_event))
        m_popUpBoxMenu->handle_event(_event);
}

void PopUpBox::logic(double passed, double deltaTime)
{

}

void PopUpBox::render(double alpha)
{
    //m_window->clear();
    m_window->draw(menuBackground);
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
