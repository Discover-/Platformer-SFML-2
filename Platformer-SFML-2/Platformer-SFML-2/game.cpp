#include <SFML\Graphics.hpp>
#include "game.h"

Game::Game()
{

}

Game::~Game()
{

}

int Game::Update()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Platformer C++ SFML", sf::Style::Close);
    sf::Event _event;

    while (window.isOpen())
    {
        window.clear(sf::Color::Green);

        while (window.pollEvent(_event))
        {
            switch (_event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        window.display();
    }

    return 0;
}
