#include <SFML/Graphics.hpp>

#include "leveleditor.hpp"
#include "statemanager.hpp"
#include "menumanager.hpp"

LevelEditor::LevelEditor(sf::RenderWindow* window, StateManager* manager)
{
    m_manager = nullptr;
    m_window = nullptr;
    m_window = window;
    m_manager = manager;
    selectedTileFilename = "";
}

void LevelEditor::handle_events()
{
    sf::Event _event;

    while (m_window->pollEvent(_event))
    {
        switch (_event.type)
        {
            case sf::Event::Closed:
                m_manager->set_next_state(StateManager::GameStates::GAME_STATE_EXIT);
                break;
            case sf::Event::MouseButtonPressed:
            {
                switch (_event.mouseButton.button)
                {
                    case sf::Mouse::Left:
                        MouseButtonPressed(sf::Mouse::getPosition(*m_window));

                        //! TODO: Hacky...
                        if (GameState* sideState = m_manager->GetSideRunningState())
                            ((MenuManager*)sideState)->MouseButtonPressed(sf::Mouse::getPosition(*m_window));
                        break;
                    case sf::Mouse::Right:
                        break;
                }
                break;
            }
            case sf::Event::KeyReleased:
            {
                switch (_event.key.code)
                {
                    case sf::Keyboard::F4:
                        break;
                }
            }
            default:
                break;
        }
    }
}

void LevelEditor::logic(double passed, double deltaTime)
{

}

void LevelEditor::render(double alpha, bool onlyDraw /* = false */)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

    if (!onlyDraw)
        m_window->clear(sf::Color::Cyan);

    sf::RectangleShape backgroundImage(sf::Vector2f(500.0f, 300.0f));
    backgroundImage.setFillColor(sf::Color::Cyan);
    m_window->draw(backgroundImage);

    if (selectedTileFilename != "")
    {
        sf::Sprite selectedTile(m_manager->resourceManager.getTexture(selectedTileFilename));
        selectedTile.setPosition(float(mousePos.x), float(mousePos.y));
        selectedTile.setColor(sf::Color(255, 255, 255, 100));
        m_window->draw(selectedTile);
    }

    for (std::vector<std::pair<sf::Vector2f, std::string> >::iterator itr = sprites.begin(); itr != sprites.end(); ++itr)
    {
        sf::Sprite sprite(m_manager->resourceManager.getTexture((*itr).second));
        sprite.setPosition((*itr).first.x, (*itr).first.y);
        m_window->draw(sprite);
    }

    if (!onlyDraw)
        m_window->display();
}

void LevelEditor::MouseButtonPressed(sf::Vector2i mousePos)
{

}
