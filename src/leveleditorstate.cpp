#include "leveleditorstate.hpp"
#include "inlinefunctions.hpp"

LevelEditorState::LevelEditorState(sf::RenderWindow* renderWindow, StateManager* manager) : m_manager(manager), m_window(renderWindow)
{
    m_levelEditorMenu = new LevelEditorMenu(&m_manager->resourceManager);
    m_levelEditorMenu->button_save.setCallback(&save, this);
    m_levelEditorMenu->button_toggleGrid.setCallback(&toggleGrid, this);
    m_levelEditorMenu->button_clear.setCallback(&clear, this);

    //tile buttons
    m_levelEditorMenu->button_tiles_block1.setCallback(&setSelectedTile, this);
    m_levelEditorMenu->button_tiles_block2.setCallback(&setSelectedTile, this);
    m_levelEditorMenu->button_tiles_block3.setCallback(&setSelectedTile, this);

    //m_levelEditorMenu->button_tiles.setCallback(&tiles, this); //! NOT needed (duh :p)

    //m_levelEditorMenu->button_tiles.items.push_back(new Button(sf::Vector2f(20.0f, 100.0f), m_manager->resourceManager.getTexture("Graphics/Menu/block1.png")));
    //m_levelEditorMenu->button_tiles.items.push_back(new Button(sf::Vector2f(120.0f, 100.0f), m_manager->resourceManager.getTexture("Graphics/Menu/block2.png")));
    //m_levelEditorMenu->button_tiles.items.push_back(new Button(sf::Vector2f(220.0f, 100.0f), m_manager->resourceManager.getTexture("Graphics/Menu/block3.png")));

    //for (std::list<std::pair<MenuItem*, std::string> >::iterator itr = m_levelEditorMenu->button_tiles.items.begin(); itr != m_levelEditorMenu->button_tiles.items.end(); ++itr)
    //    if (MenuItem* menuItem = (*itr).first)
    //        ((Button*)menuItem)->setCallback(&setSelectedTile, this, (*itr).second);

    selectedTileFilename = "";
    selectionRespectsGrid = true;
    enabledGrid = true;
    justReselectedTile = false;
    movedCursorOutOfNewTile = true;
    testingLevelOut = false;

    sf::VertexArray lines(sf::LinesStrip, 5);

    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 20; ++j)
        {
            //! Draw the lines in a rectangle formation.
            lines[0].position = sf::Vector2f(j * 50.0f, i * 50.0f);
            lines[1].position = sf::Vector2f(j * 50.0f, i * 50.0f + 50.0f);
            lines[2].position = sf::Vector2f(j * 50.0f + 50.0f, i * 50.0f + 50.0f);
            lines[3].position = sf::Vector2f(j * 50.0f + 50.0f, i * 50.0f);
            lines[4].position = lines[0].position; //! Point back to the start point.

            for (int x = 0; x < 5; ++x) //! Set '5' to '4' for a pretty neat effect :)
                lines[x].color = sf::Color::Black;

            grid.push_back(lines);
        }
    }
}

void LevelEditorState::handle_events()
{
    sf::Event _event;

    while (m_window->pollEvent(_event))
    {
        m_levelEditorMenu->handle_event(_event);

        switch (_event.type)
        {
            case sf::Event::Closed:
                m_manager->set_next_state(GAME_STATE_EXIT);
                break;
            case sf::Event::MouseButtonPressed:
            {
                switch (_event.mouseButton.button)
                {
                    case sf::Mouse::Left:
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
                    case sf::Keyboard::F7:
                        selectedTileFilename = "Graphics/Menu/block1.png";
                        break;
                    case sf::Keyboard::F8:
                        selectedTileFilename = "Graphics/Menu/block2.png";
                        break;
                    case sf::Keyboard::F9:
                        selectedTileFilename = "Graphics/Menu/block3.png";
                        break;
                }
            }
            default:
                break;
        }
    }
}

bool LevelEditorState::IsSpotTakenBySprite(sf::Vector2f position)
{
    for (std::vector<SpriteInfo>::iterator itr = sprites.begin(); itr != sprites.end(); ++itr)
        if ((*itr).position == position)
            return true;

    return false;
}

sf::Vector2f LevelEditorState::GetPositionForSelectedTile()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

    if (enabledGrid && selectedTileFilename != "" && selectionRespectsGrid)
    {
        sf::Vector2f closestPosition = sf::Vector2f(0.0f, 0.0f);

        for (std::vector<sf::VertexArray>::iterator itr = grid.begin(); itr != grid.end(); ++itr)
        {
            if (IsSpotTakenBySprite(sf::Vector2f((*itr)[0].position.x, (*itr)[0].position.y)))
                continue;

            if (GetDistance(float(mousePos.x), float(mousePos.y), (*itr)[0].position.x + 25.0f, (*itr)[0].position.y + 25.0f) < GetDistance(float(mousePos.x), float(mousePos.y), closestPosition.x + 25.0f, closestPosition.y + 25.0f))
                closestPosition = (*itr)[0].position;
        }

        return closestPosition;
    }
    else
        return sf::Vector2f(float(mousePos.x), float(mousePos.y));
}

void LevelEditorState::logic(double passed, double deltaTime)
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

void LevelEditorState::render(double alpha)
{
    m_window->clear(sf::Color::Cyan);

    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

    sf::RectangleShape backgroundImage(sf::Vector2f(1000.0f, 600.0f));
    backgroundImage.setFillColor(sf::Color::Cyan);
    m_window->draw(backgroundImage);

    if (enabledGrid)
        for (std::vector<sf::VertexArray>::iterator itr = grid.begin(); itr != grid.end(); ++itr)
            m_window->draw(*itr);

    if (selectedTileFilename != "")
    {
        sf::Sprite selectedTile(m_manager->resourceManager.getTexture(selectedTileFilename));

        bool forceIgnoreGrid = false;

        for (std::vector<SpriteInfo>::iterator itr = sprites.begin(); itr != sprites.end(); ++itr)
        {
            if ((*itr).filename == selectedTileFilename)
            {
                forceIgnoreGrid = (*itr).forceIgnoreGrid;
                break;
            }
        }

        selectedTile.setPosition(forceIgnoreGrid ? sf::Vector2f(sf::Mouse::getPosition()) : GetPositionForSelectedTile());

        selectedTile.setColor(sf::Color(255, 255, 255, 100));
        m_window->draw(selectedTile);
    }

    bool foundHoverOverTile = false;

    for (std::vector<SpriteInfo>::iterator itr = sprites.begin(); itr != sprites.end(); ++itr)
    {
        sf::Sprite sprite(m_manager->resourceManager.getTexture((*itr).filename));
        sprite.setPosition((*itr).position.x, (*itr).position.y);
        sf::FloatRect spriteRect = sprite.getGlobalBounds();

        if (selectedTileFilename == "")
        {
            if (WillCollision(float(mousePos.x), float(mousePos.y), 16.0f, 16.0f, (*itr).position.x, (*itr).position.y, spriteRect.height, spriteRect.width))
            {
                if (!foundHoverOverTile && ((*itr == sprites.back() && movedCursorOutOfNewTile) || *itr != sprites.back()))
                {
                    foundHoverOverTile = true;
                    sprite.setColor(sf::Color(255, 255, 255, 100));
                }
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

    m_window->draw(*m_levelEditorMenu); //! Draw the menu as last part of the level editor
    m_window->display();
}

void LevelEditorState::MouseButtonPressed(sf::Vector2i mousePos, bool leftMouseClick)
{
    if (selectedTileFilename == "" || !leftMouseClick)
    {
        for (std::vector<SpriteInfo>::iterator itr = sprites.begin(); itr != sprites.end(); )
        {
            sf::Sprite sprite(m_manager->resourceManager.getTexture((*itr).filename));
            sf::FloatRect spriteRect = sprite.getGlobalBounds();

            if (WillCollision(float(mousePos.x), float(mousePos.y), 16.0f, 16.0f, (*itr).position.x, (*itr).position.y, spriteRect.height, spriteRect.width))
            {
                if (leftMouseClick)
                {
                    justReselectedTile = true;
                    selectedTileFilename = (*itr).filename;
                    selectionRespectsGrid = !(*itr).forceIgnoreGrid;;
                }

                itr = sprites.erase(itr);
                break;
            }
            else
                ++itr;
        }
    }

    if (selectedTileFilename != "")
    {
        if (justReselectedTile)
        {
            justReselectedTile = false;
            return;
        }

        SpriteInfo spriteInfo;
        spriteInfo.filename = selectedTileFilename;
        spriteInfo.forceIgnoreGrid = selectedTileFilename == "Graphics/Menu/collision_pointer.png";
        spriteInfo.isCollidable = selectedTileFilename != "Graphics/Menu/collision_pointer.png";
        spriteInfo.position = GetPositionForSelectedTile();
        spriteInfo.priorityInDrawing = selectedTileFilename == "Graphics/Menu/collision_pointer.png"; //! NYI!
        sprites.push_back(spriteInfo);

        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
        {
            selectedTileFilename = "";
            selectionRespectsGrid = true;
            movedCursorOutOfNewTile = false;
        }
    }
}

void LevelEditorState::save(void* inst, Button* button)
{
    ((LevelEditorState*)inst)->m_manager->set_next_state(GAME_STATE_EXIT);
}

//void LevelEditorState::tiles(void* inst, CollapsableButton* button)
//{
//    ((LevelEditorState*)inst)->m_levelEditorMenu->button_tiles.collapsed = !self->m_levelEditorMenu->button_tiles.collapsed;
//}

void LevelEditorState::toggleGrid(void* inst, Button* button)
{
    ((LevelEditorState*)inst)->enabledGrid = !((LevelEditorState*)inst)->enabledGrid;
}

void LevelEditorState::setSelectedTile(void* inst, Button* button)
{
    LevelEditorState* self = ((LevelEditorState*)inst);
    //Check which button called, so we can determine which block we should set
    if (button == &self->m_levelEditorMenu->button_tiles_block1)
        self->SetSelectedTileFilename("Graphics/Menu/block1.png");
    if (button == &self->m_levelEditorMenu->button_tiles_block2)
        self->SetSelectedTileFilename("Graphics/Menu/block2.png");
    if (button == &self->m_levelEditorMenu->button_tiles_block3)
        self->SetSelectedTileFilename("Graphics/Menu/block3.png");
}

void LevelEditorState::clear(void* inst, Button* button)
{
    ((LevelEditorState*)inst)->sprites.clear();
}
