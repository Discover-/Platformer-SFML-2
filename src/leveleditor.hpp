#pragma once

#include <vector>

#include "gamestate.hpp"

class LevelEditor : public GameState
{
    public:
        LevelEditor(sf::RenderWindow* renderWindow, StateManager* manager);

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha, bool onlyDraw = false);

        void MouseButtonPressed(sf::Vector2i mousePos, bool leftMouseClick);

        void SetSelectedTileFilename(std::string filename) { selectedTileFilename = filename; }
        std::string GetSelectedTileFilename() { return selectedTileFilename; }
        bool HasSelectedTile() { return selectedTileFilename != ""; }

        void AddSprite(sf::Vector2f pos, std::string filename) { sprites.push_back(std::make_pair(pos, filename)); }

        void SetEnabledGrid(bool val);
        bool IsGridEnabled();

        sf::Vector2f GetPositionForSelectedTile();
        bool IsSpotTakenBySprite(sf::Vector2f position);

        bool justReselectedTile, justPlacedNewTile, movedCursorOutOfNewTile;

    private:
        StateManager* m_manager;
        sf::RenderWindow* m_window;
        std::string selectedTileFilename;
        std::vector<std::pair<sf::Vector2f, std::string> > sprites;
        bool enabledGrid;
        sf::RectangleShape grid[20][12];
};
