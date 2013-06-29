#include <SFML/Graphics.hpp>

#include <iostream>

#include "leveleditor.hpp"
#include "statemanager.hpp"
#include "menumanager.hpp"

LevelEditor::LevelEditor(sf::RenderWindow* window, StateManager* manager)
:m_window(window),
m_manager(manager),
m_menuManager(m_window, m_manager, MENU_STATE_LEVEL_EDITOR)
{
    selectedTileFilename = "";
    selectionRespectsGrid = true;
    enabledGrid = true;
    justReselectedTile = false;
    justPlacedNewTile = false;
    movedCursorOutOfNewTile = true;
    testingLevelOut = false;

    sf::RectangleShape gridShape(sf::Vector2f(50.0f, 50.0f));
    gridShape.setFillColor(sf::Color::Transparent);
    gridShape.setOutlineColor(sf::Color::Black);
    //gridShape.setOutlineColor(sf::Color(255, 255, 255, 10));
    gridShape.setOutlineThickness(1.0f);

    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            gridShape.setPosition(j * 50.0f, i * 50.0f);
            grid[j][i] = gridShape;
        }
    }
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
                        m_menuManager.MouseButtonPressed(sf::Mouse::getPosition(*m_window));
                        MouseButtonPressed(sf::Mouse::getPosition(*m_window), true);
                        break;
                    case sf::Mouse::Right:
                        MouseButtonPressed(sf::Mouse::getPosition(*m_window), false);
                        break;
                }
                break;
            }
            case sf::Event::KeyReleased:
            {
                switch (_event.key.code)
                {
                    case sf::Keyboard::F1:
                    case sf::Keyboard::F2:
                        //! Handled in Unit::Update
                        break;
                    case sf::Keyboard::F3:
                        enabledGrid = !enabledGrid;
                        break;
                    case sf::Keyboard::F4:
                        testingLevelOut = !testingLevelOut;
                        break;
                }
            }
            default:
                break;
        }
    }
}

//! TODO: Make this inlin and spare functions like these in some place...
float GetDistance(float x1, float y1, float x2, float y2)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    float dist = sqrt((dx * dx) + (dy * dy));
    return (dist > 0 ? dist : 0);
}

bool LevelEditor::IsSpotTakenBySprite(sf::Vector2f position)
{
    for (std::vector<std::pair<sf::Vector2f, std::string> >::iterator itr = sprites.begin(); itr != sprites.end(); ++itr)
        if ((*itr).first == position)
            return true;

    return false;
}

sf::Vector2f LevelEditor::GetPositionForSelectedTile()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

    if (enabledGrid && selectedTileFilename != "" && selectionRespectsGrid)
    {
        if (selectedTileFilename == "Graphics/Menu/collision_pointer.png")
            return sf::Vector2f(float(mousePos.x), float(mousePos.y));

        sf::RectangleShape closestGrid = grid[0][0];

        for (int i = 0; i < 12; ++i)
        {
            for (int j = 0; j < 20; ++j)
            {
                sf::Vector2f gridPos = grid[j][i].getPosition();

                if (IsSpotTakenBySprite(gridPos))
                    continue;

                sf::Vector2f closestGridPos = closestGrid.getPosition();

                //! We add 25.0f because that's 50% of the width and height of the grid block, which means we therefore target the center of that grid
                //! spot so the closestGrid variable only changes when we actually enter a grid block with our cursor.
                if (GetDistance(float(mousePos.x), float(mousePos.y), gridPos.x + 25.0f, gridPos.y + 25.0f) < GetDistance(float(mousePos.x), float(mousePos.y), closestGridPos.x + 25.0f, closestGridPos.y + 25.0f))
                    closestGrid = grid[j][i];
            }
        }

        return closestGrid.getPosition();
    }
    else
        return sf::Vector2f(float(mousePos.x), float(mousePos.y));
}

void LevelEditor::logic(double passed, double deltaTime)
{
    if (testingLevelOut)
    {
        if (!player)
        {
            sf::RectangleShape bodyShape(sf::Vector2f(75.0f, 75.0f));
            bodyShape.setFillColor(sf::Color::Green);
            player = new Player(m_window, sf::Vector2f(500.0f, 300.0f), bodyShape, m_manager, this);
        }

        player->Update();
    }
}

void LevelEditor::render(double alpha)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

    m_window->clear(sf::Color::Cyan);

    sf::RectangleShape backgroundImage(sf::Vector2f(1000.0f, 600.0f));
    backgroundImage.setFillColor(sf::Color::Cyan);
    m_window->draw(backgroundImage);

    if (enabledGrid)
        for (int i = 0; i < 12; ++i)
            for (int j = 0; j < 20; ++j)
                m_window->draw(grid[j][i]);

    if (selectedTileFilename != "")
    {
        sf::Sprite selectedTile(m_manager->resourceManager.getTexture(selectedTileFilename));
        selectedTile.setPosition(GetPositionForSelectedTile());
        selectedTile.setColor(sf::Color(255, 255, 255, 100));
        m_window->draw(selectedTile);
    }

    for (std::vector<std::pair<sf::Vector2f, std::string> >::iterator itr = sprites.begin(); itr != sprites.end(); ++itr)
    {
        sf::Sprite sprite(m_manager->resourceManager.getTexture((*itr).second));
        sprite.setPosition((*itr).first.x, (*itr).first.y);

        sf::FloatRect spriteRect = sprite.getGlobalBounds();

        if (selectedTileFilename == "")
        {
            if (!(mousePos.y >= (*itr).first.y + spriteRect.height || mousePos.x >= (*itr).first.x + spriteRect.width || mousePos.y + 16.0f <= (*itr).first.y || mousePos.x + 16.0f <= (*itr).first.x))
            {
                if ((*itr == sprites.back() && movedCursorOutOfNewTile) || *itr != sprites.back())
                    sprite.setColor(sf::Color(255, 255, 255, 100));
            }
            else if (*itr == sprites.back() && !movedCursorOutOfNewTile)
                movedCursorOutOfNewTile = true;
        }

        m_window->draw(sprite);
    }

    if (testingLevelOut && player)
    {
        sf::RectangleShape rectShape = player->GetBodyShape();
        rectShape.setPosition(player->GetPosition());
        m_window->draw(rectShape);
    }

    m_window->display();
}

void LevelEditor::MouseButtonPressed(sf::Vector2i mousePos, bool leftMouseClick)
{
    //! Temporarily for testing...
    //if (mousePos.x > 300)
    //    enabledGrid = !enabledGrid;

    if (leftMouseClick && justPlacedNewTile)
    {
        justPlacedNewTile = false;
        return;
    }

    if (selectedTileFilename == "" || !leftMouseClick)
    {
        for (std::vector<std::pair<sf::Vector2f, std::string> >::iterator itr = sprites.begin(); itr != sprites.end(); )
        {
            sf::Sprite sprite(m_manager->resourceManager.getTexture((*itr).second));
            sf::FloatRect spriteRect = sprite.getGlobalBounds();

            if (!(mousePos.y >= (*itr).first.y + spriteRect.height || mousePos.x >= (*itr).first.x + spriteRect.width || mousePos.y + 16.0f <= (*itr).first.y || mousePos.x + 16.0f <= (*itr).first.x))
            {
                if (leftMouseClick)
                {
                    justReselectedTile = true;
                    selectedTileFilename = (*itr).second;

                    if ((*itr).second == "Graphics/Menu/collision_pointer.png")
                        selectionRespectsGrid = false;
                }

                itr = sprites.erase(itr);
                break;
            }
            else
                ++itr;
        }
    }
}

void LevelEditor::SetEnabledGrid(bool val)
{
    enabledGrid = false;
}

bool LevelEditor::IsGridEnabled()
{
    return enabledGrid;
}
