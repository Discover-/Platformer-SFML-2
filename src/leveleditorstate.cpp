#include "leveleditorstate.hpp"
#include "inlinefunctions.hpp"

LevelEditorState::LevelEditorState(sf::RenderWindow* renderWindow, StateManager* manager) : m_manager(manager), m_window(renderWindow)
{
    m_levelEditorMenu = new LevelEditorMenu(&m_manager->resourceManager);
    m_levelEditorMenu->button_save.setCallback(&save, this);
    m_levelEditorMenu->button_toggleGrid.setCallback(&toggleGrid, this);
    m_levelEditorMenu->button_clear.setCallback(&clear, this);

    //! Tiles buttons
    m_levelEditorMenu->button_tiles_block1.setCallback(&setSelectedTile, this);
    m_levelEditorMenu->button_tiles_block2.setCallback(&setSelectedTile, this);
    m_levelEditorMenu->button_tiles_block3.setCallback(&setSelectedTile, this);
    m_levelEditorMenu->button_tiles_collisionPointer.setCallback(&setSelectedTile, this);

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
    drawingCollisionLine = false;

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

    collisionLineSelection.setPrimitiveType(sf::LinesStrip);
    collisionLineSelection.resize(2);

    for (int x = 0; x < 2; ++x)
    {
        collisionLineSelection[x].color = sf::Color::Red;
        collisionLineSelection[x].position = sf::Vector2f(0.0f, 0.0f);
    }
}

void LevelEditorState::handle_events()
{
    sf::Event _event;
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

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
                    case sf::Mouse::Right:
                        MouseButtonPressed(mousePos, _event.mouseButton.button == sf::Mouse::Left);
                        break;
                    default:
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
                    default:
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
            if (!IsSpotTakenBySprite((*itr)[0].position))
                if (GetDistance(float(mousePos.x), float(mousePos.y), (*itr)[0].position.x + 25.0f, (*itr)[0].position.y + 25.0f) < GetDistance(float(mousePos.x), float(mousePos.y), closestPosition.x + 25.0f, closestPosition.y + 25.0f))
                    closestPosition = (*itr)[0].position;

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

    if (enabledGrid)
        for (std::vector<sf::VertexArray>::iterator itr = grid.begin(); itr != grid.end(); ++itr)
            m_window->draw(*itr);

    for (std::vector<sf::VertexArray>::iterator itr = collisionLines.begin(); itr != collisionLines.end(); ++itr)
        m_window->draw(*itr);

    if (selectedTileFilename != "")
    {
        sf::Sprite selectedTile(m_manager->resourceManager.getTexture(selectedTileFilename));
        selectedTile.setPosition(GetPositionForSelectedTile());
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

    if (drawingCollisionLine)
    {
        collisionLineSelection[1].position = sf::Vector2f(float(mousePos.x), float(mousePos.y));
        m_window->draw(collisionLineSelection);
    }

    m_window->draw(*m_levelEditorMenu); //! Draw the menu as last part of the level editor
    m_window->display();
}

void LevelEditorState::MouseButtonPressed(sf::Vector2i mousePos, bool leftMouseClick)
{
    if (selectedTileFilename == "" || !leftMouseClick)
    {
        bool shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

        for (std::vector<SpriteInfo>::iterator itr = sprites.begin(); itr != sprites.end(); )
        {
            sf::Sprite sprite(m_manager->resourceManager.getTexture((*itr).filename));
            sf::FloatRect spriteRect = sprite.getGlobalBounds();

            if (WillCollision(float(mousePos.x), float(mousePos.y), 16.0f, 16.0f, (*itr).position.x, (*itr).position.y, spriteRect.height, spriteRect.width))
            {
                bool eraseItr = true;

                if (leftMouseClick)
                {
                    if ((*itr).filename == "Graphics/Menu/collision_pointer.png")
                    {
                        eraseItr = false;

                        if (!drawingCollisionLine)
                        {
                            if (shiftPressed)
                            {
                                drawingCollisionLine = true;
                                collisionLineSelection[0].position = sf::Vector2f((*itr).position.x + 10.0f, (*itr).position.y + 10.0f);
                            }
                            else
                            {
                                justReselectedTile = true;
                                selectedTileFilename = (*itr).filename;
                                selectionRespectsGrid = !(*itr).forceIgnoreGrid;
                            }       
                        }
                        else
                        {
                            drawingCollisionLine = shiftPressed;
                            sf::VertexArray lines(sf::LinesStrip, 2);
                            lines[0].position = collisionLineSelection[0].position;
                            lines[1].position = sf::Vector2f((*itr).position.x + 10.0f, (*itr).position.y + 10.0f);

                            if (shiftPressed)
                                collisionLineSelection[0] = collisionLineSelection[1];

                            for (int x = 0; x < 2; ++x)
                            {
                                lines[x].color = sf::Color::Red;

                                if (!shiftPressed)
                                    collisionLineSelection[x].position = sf::Vector2f(0.0f, 0.0f);
                            }

                            collisionLines.push_back(lines);

                            CollidableObject collidableObject;
                            collidableObject.position = lines[0].position;
                            collidableObject.collideFromTopOnly = true;
                            collidableObject.width = std::max(lines[0].position.x, lines[1].position.x) - std::min(lines[0].position.x, lines[1].position.x);
                            collidableObject.height = 5.0f;
                            collidableObjects.push_back(collidableObject);
                        }
                    }
                    else
                    {
                        justReselectedTile = true;
                        selectedTileFilename = (*itr).filename;
                        selectionRespectsGrid = !(*itr).forceIgnoreGrid;
                    }
                }

                if (eraseItr)
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
        spriteInfo.priorityInDrawing = false; //! NYI!
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
    else if (button == &self->m_levelEditorMenu->button_tiles_block2)
        self->SetSelectedTileFilename("Graphics/Menu/block2.png");
    else if (button == &self->m_levelEditorMenu->button_tiles_block3)
        self->SetSelectedTileFilename("Graphics/Menu/block3.png");
    else if (button == &self->m_levelEditorMenu->button_tiles_collisionPointer)
        self->SetSelectedTileFilename("Graphics/Menu/collision_pointer.png");
    else
        return;

    self->selectionRespectsGrid = button->respectsGridWhenSelected;
}

void LevelEditorState::clear(void* inst, Button* button)
{
    ((LevelEditorState*)inst)->sprites.clear();
}
