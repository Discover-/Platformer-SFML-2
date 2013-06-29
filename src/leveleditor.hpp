#pragma once

#include <vector>

#include "gamestate.hpp"
#include "player.hpp"

class LevelEditor : public GameState
{
    public:
        LevelEditor(sf::RenderWindow* renderWindow, StateManager* manager);

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha, bool onlyDraw = false);

        void MouseButtonPressed(sf::Vector2i mousePos, bool leftMouseClick);

        void SetSelectedTileFilename(std::string filename, bool _selectionRespectsGrid = true) { selectedTileFilename = filename; selectionRespectsGrid = _selectionRespectsGrid; }
        std::string GetSelectedTileFilename() { return selectedTileFilename; }
        bool HasSelectedTile() { return selectedTileFilename != ""; }

        void AddSprite(sf::Vector2f pos, std::string filename) { sprites.push_back(std::make_pair(pos, filename)); }
        std::vector<std::pair<sf::Vector2f, std::string> >& GetSprites() { return sprites; }

        void SetEnabledGrid(bool val);
        bool IsGridEnabled();

        sf::Vector2f GetPositionForSelectedTile();
        bool IsSpotTakenBySprite(sf::Vector2f position);

        bool justReselectedTile, justPlacedNewTile, movedCursorOutOfNewTile;
        bool testingLevelOut;

    private:
        StateManager* m_manager;
        sf::RenderWindow* m_window;
        std::string selectedTileFilename;
        bool selectionRespectsGrid;
        std::vector<std::pair<sf::Vector2f, std::string> > sprites;
        bool enabledGrid;
        sf::RectangleShape grid[20][12];
        Player* player;
};
