#include <iostream>
#include <list>

#include "leveleditorstate.hpp"
#include "inlinefunctions.hpp"

LevelEditorState::LevelEditorState(sf::RenderWindow* renderWindow, StateManager* manager) : m_manager(manager), m_window(renderWindow)
{
    m_tileSetWindow = new sf::RenderWindow(sf::VideoMode(590, 300), "Platformer C++ SFML - Tileset", sf::Style::Close | sf::Style::Resize);
    m_tileSetWindow->setPosition(sf::Vector2i(m_window->getPosition().x + 1015, m_window->getPosition().y));
    prevTilesetWindowPos = sf::Vector2i(0, 0);

    m_levelEditorMenu = new LevelEditorMenu(&m_manager->resourceManager);
    m_levelEditorMenu->button_test.setCallback(&testOut, this);
    m_levelEditorMenu->button_save.setCallback(&save, this);
    m_levelEditorMenu->button_toggleGrid.setCallback(&toggleGrid, this);
    m_levelEditorMenu->button_clear.setCallback(&clear, this);
    m_levelEditorMenu->button_toggleCollisionLines.setCallback(&toggleCollisionLines, this);

    //! Tiles buttons
    for (int i = 0; i < BUTTONT_TILES_CHILDS_SIZE; ++i)
        m_levelEditorMenu->button_tiles_childs[i].setCallback(&setSelectedTile, this);

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
    minimizedWindow = false;

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

    m_popUpBox = new PopUpBox(m_window, m_manager, "Are you sure you want to exit without saving?", sf::Vector2f(350.0f, 250.0f));
    m_showPopupBox = false;

    gameState = GAME_STATE_LEVEL_EDITOR;
    gameStateAfterPopUpBox = GAME_STATE_NULL;

    m_placeTileWithCtrl = false;

    m_showCollisionLines = true;

    selectedZindex = 1;
}

LevelEditorState::~LevelEditorState()
{
    delete m_tileSetWindow;
    delete m_levelEditorMenu;
    delete m_popUpBox;
    delete player;
}

void LevelEditorState::handle_events()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

    if (m_showPopupBox)
    {
        if (m_popUpBox->m_pressedCloseBox || m_popUpBox->m_pressedNo)
        {
            m_popUpBox->resetPositions();
            m_popUpBox->m_pressedNo = false;
            m_popUpBox->m_pressedYes = false;
            m_popUpBox->m_pressedCloseBox = false;
            m_showPopupBox = false;
        }
        else if (!m_popUpBox->m_pressedNo && m_popUpBox->m_pressedYes)
        {
            m_tileSetWindow->close();
            m_manager->set_next_state(gameStateAfterPopUpBox != GAME_STATE_NULL ? gameStateAfterPopUpBox : GAME_STATE_MENU);
        }
    }

    sf::Event _event;

    while (m_window->pollEvent(_event))
    {
        if (m_showPopupBox)
            m_popUpBox->handle_events();

        switch (_event.type)
        {
            case sf::Event::Closed:
            {
                if (!m_showPopupBox && !m_popUpBox->m_pressedYes && !sprites.empty())
                {
                    gameStateAfterPopUpBox = GAME_STATE_EXIT;
                    drawingCollisionLine = false;
                    selectedTileFilename = "";
                    m_showPopupBox = true;
                    selectedZindex = 1;
                    break;
                }
                else if ((!m_showPopupBox && sprites.empty()) || m_popUpBox->m_pressedYes)
                    m_manager->set_next_state(GAME_STATE_EXIT);
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                switch (_event.mouseButton.button)
                {
                    case sf::Mouse::Left:
                    case sf::Mouse::Right:
                    {
                        if (m_showPopupBox)
                            break;

                        if (selectedTileFilename != "" && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))
                            m_placeTileWithCtrl = true;
                        else
                        {
                            m_placeTileWithCtrl = false;
                            MouseButtonPressed(mousePos, _event.mouseButton.button == sf::Mouse::Left);
                        }
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                if (m_showPopupBox)
                    break;

                m_placeTileWithCtrl = false;
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
                        if (m_showPopupBox)
                            break;

                        enabledGrid = !enabledGrid;
                        break;
                    case sf::Keyboard::Escape:
                    {
                        if (m_showPopupBox)
                        {
                            m_showPopupBox = false;
                            m_popUpBox->resetPositions();
                        }
                        else if (selectedTileFilename != "")
                        {
                            justReselectedTile = false;
                            selectedTileFilename = "";
                            selectionRespectsGrid = true;
                            selectedZindex = 1;
                        }
                        else if (drawingCollisionLine)
                            drawingCollisionLine = false;
                        break;
                    }
                    default:
                        break;
                }
            }
            default:
                break;
        }
    }

    if (minimizedWindow && m_window->getPosition().x > -3000.0f)
    {
        m_tileSetWindow->setPosition(prevTilesetWindowPos);
        prevTilesetWindowPos = sf::Vector2i(0, 0);
    }

    minimizedWindow = m_window->getPosition().x < -3000.0f;

    if (minimizedWindow && prevTilesetWindowPos.x == 0)
    {
        prevTilesetWindowPos = m_tileSetWindow->getPosition();
        m_tileSetWindow->setPosition(m_window->getPosition());
    }

    while (m_tileSetWindow->pollEvent(_event))
    {
        m_levelEditorMenu->handle_event(_event);

        switch (_event.type)
        {
            case sf::Event::Closed:
            {
                if (!m_showPopupBox && !sprites.empty())
                {
                    m_showPopupBox = true;
                    selectedTileFilename = "";
                    drawingCollisionLine = false;
                    gameStateAfterPopUpBox = GAME_STATE_MENU;
                    selectedZindex = 1;
                    break;
                }
                else if (sprites.empty())
                {
                    m_tileSetWindow->close();
                    m_manager->set_next_state(GAME_STATE_MENU);
                }
                break;
            }
            case sf::Event::Resized:
            {
                m_tileSetWindow->setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(m_tileSetWindow->getSize().x), static_cast<float>(m_tileSetWindow->getSize().y))));
                break;
            }
            default:
                break;
        }
    }

    if (!m_showPopupBox && m_placeTileWithCtrl)
    {
        if (selectedTileFilename != "")
        {
            sf::Vector2f positionForSelectedTile = GetPositionForSelectedTile();

            if (!(positionForSelectedTile.x < 0.0f || positionForSelectedTile.y < 0.0f))
            {
                SpriteInfo spriteInfo;
                spriteInfo.filename = selectedTileFilename;
                spriteInfo.forceIgnoreGrid = selectedTileFilename == "Graphics/Menu/collision_pointer.png";
                spriteInfo.isCollidable = selectedTileFilename != "Graphics/Menu/collision_pointer.png";
                spriteInfo.position = positionForSelectedTile;
                spriteInfo.zIndex = selectedZindex;
                sprites.push_back(spriteInfo);
            }
        }
        else
            m_placeTileWithCtrl = false;
    }
}

bool LevelEditorState::IsSpotTakenBySprite(sf::Vector2f position)
{
    if (!enabledGrid || sprites.empty())
        return false;

    for (std::vector<SpriteInfo>::iterator itr = sprites.begin(); itr != sprites.end(); ++itr)
        if ((*itr).position == position)
            return true;

    return false;
}

sf::Vector2f LevelEditorState::GetPositionForSelectedTile()
{
    if (selectedTileFilename == "")
        return sf::Vector2f(0.0f, 0.0f);

    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

    if (enabledGrid && selectionRespectsGrid)
    {
        sf::Vector2f closestPosition = sf::Vector2f(-50.0f, -50.0f);

        for (std::vector<sf::VertexArray>::iterator itr = grid.begin(); itr != grid.end(); ++itr)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
            {
                if (WillCollision(float(mousePos.x), float(mousePos.y), 0.0f, 0.0f, (*itr)[0].position.x, (*itr)[0].position.y, 50.0f, 50.0f))
                    return IsSpotTakenBySprite((*itr)[0].position) ? closestPosition : sf::Vector2f((*itr)[0].position.x, (*itr)[0].position.y);
            }
            else if (!IsSpotTakenBySprite((*itr)[0].position))
                if (GetDistance(float(mousePos.x), float(mousePos.y), (*itr)[0].position.x + 25.0f, (*itr)[0].position.y + 25.0f) < GetDistance(float(mousePos.x), float(mousePos.y), closestPosition.x + 25.0f, closestPosition.y + 25.0f))
                    closestPosition = (*itr)[0].position;
        }

        return closestPosition;
    }
    else
    {
        float returnPosX = float(mousePos.x);
        float returnPosY = float(mousePos.y);
        sf::Sprite selectedTileSprite(m_manager->resourceManager.getTexture(selectedTileFilename));
        sf::FloatRect selectedTileRect = selectedTileSprite.getGlobalBounds();

        if (returnPosX + selectedTileRect.width > 1000.0f)
            returnPosX = 1000.0f - selectedTileRect.width;

        if (returnPosY + selectedTileRect.height > 600.0f)
            returnPosY = 600.0f - selectedTileRect.height;

        if (returnPosX < 0.0f)
            returnPosX = 0.0f;

        if (returnPosY < 0.0f)
            returnPosY = 0.0f;

        if (returnPosX == float(mousePos.x) && returnPosY == float(mousePos.y))
        {
            returnPosX -= selectedTileRect.width / 2.0f;
            returnPosY -= selectedTileRect.height / 2.0f;
        }

        return sf::Vector2f(returnPosX, returnPosY);
    }
}

void LevelEditorState::logic(double passed, double deltaTime)
{
    if (m_showPopupBox)
        m_popUpBox->logic(passed, deltaTime);
    else
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
}

void LevelEditorState::render(double alpha)
{
    m_window->clear(sf::Color::Cyan);
    m_tileSetWindow->clear(sf::Color::Cyan);

    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

    if (enabledGrid)
        for (std::vector<sf::VertexArray>::iterator itr = grid.begin(); itr != grid.end(); ++itr)
            m_window->draw(*itr);

    if (m_showCollisionLines)
        for (std::vector<sf::VertexArray>::iterator itr = collisionLines.begin(); itr != collisionLines.end(); ++itr)
            m_window->draw(*itr);

    bool foundHoverOverTile = false;

    std::vector<SpriteInfo> sortedSprites = sprites;
    std::sort(sortedSprites.begin(), sortedSprites.end(), SortSpritesByZIndex());
    std::vector<SpriteInfo> sortedSpritesCopy = sortedSprites;

    for (std::vector<SpriteInfo>::iterator itr = sortedSprites.begin(); itr != sortedSprites.end(); ++itr)
    {
        if (!m_showCollisionLines && (*itr).filename == "Graphics/Menu/collision_pointer.png")
            continue;

        sf::Sprite sprite(m_manager->resourceManager.getTexture((*itr).filename));
        sprite.setPosition((*itr).position.x, (*itr).position.y);
        sf::FloatRect spriteRect = sprite.getGlobalBounds();

        //if (selectedTileFilename == "")
        //{
        //    if (WillCollision(float(mousePos.x), float(mousePos.y), 0.0f, 0.0f, (*itr).position.x, (*itr).position.y, spriteRect.height, spriteRect.width))
        //    {
        //        if (!foundHoverOverTile && ((*itr == sprites.back() && movedCursorOutOfNewTile) || *itr != sprites.back()))
        //        {
        //            if (*itr == sortedSprites.back())
        //            {
        //                foundHoverOverTile = true;

        //                if (!m_showPopupBox)
        //                    sprite.setColor(sf::Color(255, 255, 255, 100));
        //            }
        //        }
        //    }
        //    else if (*itr == sprites.back() && !movedCursorOutOfNewTile)
        //        movedCursorOutOfNewTile = true;
        //}

        sortedSpritesCopy.push_back(*itr);
        //m_window->draw(sprite);
    }

    sf::Vector2f hoverOverTilePos(0.0f, 0.0f);

    if (selectedTileFilename == "")
    {
        std::reverse(sortedSpritesCopy.begin(), sortedSpritesCopy.end());

        for (std::vector<SpriteInfo>::iterator itr2 = sortedSpritesCopy.begin(); itr2 != sortedSpritesCopy.end(); ++itr2)
        {
            sf::Sprite sprite(m_manager->resourceManager.getTexture((*itr2).filename));
            sprite.setPosition((*itr2).position.x, (*itr2).position.y);
            sf::FloatRect spriteRect = sprite.getGlobalBounds();

            if (WillCollision(float(mousePos.x), float(mousePos.y), 0.0f, 0.0f, (*itr2).position.x, (*itr2).position.y, spriteRect.height, spriteRect.width))
            {
                hoverOverTilePos = (*itr2).position;
                break;
            }
        }
        
        std::reverse(sortedSpritesCopy.begin(), sortedSpritesCopy.end());
    }

    for (std::vector<SpriteInfo>::iterator itr3 = sortedSpritesCopy.begin(); itr3 != sortedSpritesCopy.end(); ++itr3)
    {
        sf::Sprite sprite(m_manager->resourceManager.getTexture((*itr3).filename));
        sprite.setPosition((*itr3).position.x, (*itr3).position.y);

        if (hoverOverTilePos.x != 0.0f && hoverOverTilePos.y != 0.0f && (*itr3).position == hoverOverTilePos)
            sprite.setColor(sf::Color(255, 255, 255, 100));

        m_window->draw(sprite);
    }

    if (!m_showPopupBox && selectedTileFilename != "")
    {
        sf::Sprite selectedTile(m_manager->resourceManager.getTexture(selectedTileFilename));
        selectedTile.setPosition(GetPositionForSelectedTile());
        selectedTile.setColor(sf::Color(255, 255, 255, 100));
        m_window->draw(selectedTile);
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

    if (m_showPopupBox)
        m_popUpBox->render(alpha);

    m_tileSetWindow->draw(*m_levelEditorMenu);
    m_window->display();
    m_tileSetWindow->display();
}

std::vector<SpriteInfo> erasedSprites;

void LevelEditorState::MouseButtonPressed(sf::Vector2i mousePos, bool leftMouseClick)
{
    if (selectedTileFilename == "" || !leftMouseClick)
    {
        bool shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);

        std::vector<SpriteInfo> sortedSprites = sprites;
        std::sort(sortedSprites.begin(), sortedSprites.end(), SortSpritesByZIndex());
        std::reverse(sortedSprites.begin(), sortedSprites.end());

        for (std::vector<SpriteInfo>::iterator itr = sortedSprites.begin(); itr != sortedSprites.end(); )
        //for (std::vector<SpriteInfo>::reverse_iterator itr = sortedSprites.rbegin(); itr != sortedSprites.rend(); )
        {
            if (!erasedSprites.empty())
            {
                std::vector<SpriteInfo>::iterator findIter = std::find(erasedSprites.begin(), erasedSprites.end(), *itr);

                if (findIter != erasedSprites.end())
                    continue;
            }

            sf::Sprite sprite(m_manager->resourceManager.getTexture((*itr).filename));
            sf::FloatRect spriteRect = sprite.getGlobalBounds();

            if (WillCollision(float(mousePos.x), float(mousePos.y), 0.0f, 0.0f, (*itr).position.x, (*itr).position.y, spriteRect.height, spriteRect.width))
            {
                bool eraseItr = true;

                if ((*itr).filename == "Graphics/Menu/collision_pointer.png")
                {
                    if (!leftMouseClick)
                    {
                        for (std::vector<sf::VertexArray>::iterator itr2 = collisionLines.begin(); itr2 != collisionLines.end(); )
                        {
                            if (((*itr2)[0].position.x == (*itr).position.x + 10.0f && (*itr2)[0].position.y == (*itr).position.y + 10.0f) || ((*itr2)[1].position.x == (*itr).position.x + 10.0f && (*itr2)[1].position.y == (*itr).position.y + 10.0f))
                                itr2 = collisionLines.erase(itr2);
                            else
                                ++itr2;
                        }
                    }
                    else
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
                                eraseItr = true;
                                justReselectedTile = true;
                                selectedTileFilename = (*itr).filename;
                                selectionRespectsGrid = !(*itr).forceIgnoreGrid;
                                selectedZindex = (*itr).zIndex;
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
                }
                else if (leftMouseClick)
                {
                    justReselectedTile = true;
                    selectedTileFilename = (*itr).filename;
                    selectionRespectsGrid = !(*itr).forceIgnoreGrid;
                    selectedZindex = (*itr).zIndex;
                }

                if (eraseItr)
                {
                    erasedSprites.push_back(*itr);
                    //sortedSprites.erase( --(itr.base()) );
                    //itr = sortedSprites.rbegin();

                    //sortedSprites.erase(sortedSprites.rbegin(), sortedSprites.rend());
                    //sortedSprites.erase((itr++).base());
                    //std::set<int>::iterator tempIter = sortedSprites.erase(--itr.base());
                    //rev_iter = setOfInts.erase(tempIter);
                    //sortedSprites.erase(itr);
                    //itr = sortedSprites.begin();
                }

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
        spriteInfo.zIndex = selectedZindex;
        sprites.push_back(spriteInfo);

        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
        {
            selectedTileFilename = "";
            selectionRespectsGrid = true;
            movedCursorOutOfNewTile = false;
            selectedZindex = 1;
        }
    }
}

void LevelEditorState::save(void* inst, Button* button)
{
    ((LevelEditorState*)inst)->m_showPopupBox = true;
}

void LevelEditorState::toggleGrid(void* inst, Button* button)
{
    if (((LevelEditorState*)inst)->m_showPopupBox)
        return;

    ((LevelEditorState*)inst)->enabledGrid = !((LevelEditorState*)inst)->enabledGrid;
}

void LevelEditorState::setSelectedTile(void* inst, Button* button)
{
    if (((LevelEditorState*)inst)->m_showPopupBox)
        return;

    LevelEditorState* self = (LevelEditorState*)inst;

    //! Check which button called, so we can determine which block we should set
    if (button == &self->m_levelEditorMenu->button_tiles_childs[0])
        self->SetSelectedTileFilename("Graphics/Menu/block1.png", true, 2);
    else if (button == &self->m_levelEditorMenu->button_tiles_childs[1])
        self->SetSelectedTileFilename("Graphics/Menu/block2.png", true, 3);
    else if (button == &self->m_levelEditorMenu->button_tiles_childs[2])
        self->SetSelectedTileFilename("Graphics/Menu/block3.png");
    else if (button == &self->m_levelEditorMenu->button_tiles_childs[3])
        self->SetSelectedTileFilename("Graphics/Menu/collision_pointer.png", false, 4);
    else
        std::cout << "Unknown/unsupported button in LevelEditorState::setSelectedTile" << std::endl;
}

void LevelEditorState::clear(void* inst, Button* button)
{
    if (((LevelEditorState*)inst)->m_showPopupBox)
        return;

    ((LevelEditorState*)inst)->sprites.clear();
    ((LevelEditorState*)inst)->collisionLines.clear();
}

void LevelEditorState::testOut(void* inst, Button* button)
{
    if (((LevelEditorState*)inst)->m_showPopupBox)
        return;

    ((LevelEditorState*)inst)->testingLevelOut = !((LevelEditorState*)inst)->testingLevelOut;
}

void LevelEditorState::toggleCollisionLines(void* inst, Button* button)
{
    ((LevelEditorState*)inst)->m_showCollisionLines = !((LevelEditorState*)inst)->m_showCollisionLines;
}

void LevelEditorState::SetSelectedTileFilename(std::string filename, bool _selectionRespectsGrid /* = true */, int _selectedZindex /* = 1 */) 
{
    selectedTileFilename = filename;
    selectionRespectsGrid = _selectionRespectsGrid;
    selectedZindex = _selectedZindex;
}
