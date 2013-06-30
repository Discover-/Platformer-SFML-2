#ifndef LEVELEDITORSTATE_HPP_INCLUDED
#define LEVELEDITORSTATE_HPP_INCLUDED

#include "mainmenu.hpp"
#include "button.hpp"
#include "gamestate.hpp"
#include "leveleditormenu.hpp"
#include "player.hpp"

class LevelEditorState : public GameState
{
    public:
        LevelEditorState(sf::RenderWindow* renderWindow, StateManager* manager);

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha);

        void MouseButtonPressed(sf::Vector2i mousePos, bool leftMouseClick);

        void SetSelectedTileFilename(std::string filename, bool _selectionRespectsGrid = true) { selectedTileFilename = filename; selectionRespectsGrid = _selectionRespectsGrid; }
        std::string GetSelectedTileFilename() { return selectedTileFilename; }
        bool HasSelectedTile() { return selectedTileFilename != ""; }

        void AddSprite(sf::Vector2f pos, std::string filename) { sprites.push_back(std::make_pair(pos, filename)); }
        std::vector<std::pair<sf::Vector2f, std::string> >& GetSprites() { return sprites; }

        sf::Vector2f GetPositionForSelectedTile();
        bool IsSpotTakenBySprite(sf::Vector2f position);

        //bool justReselectedTile, justPlacedNewTile, movedCursorOutOfNewTile, testingLevelOut;

        static void save(void* inst, Button* button);
        //static void tiles(void* inst, CollapsableButton* button);
        static void toggleGrid(void* inst, Button* button);
        static void setSelectedTile(void* inst, Button* button, std::string filename);

    private:
        sf::RenderWindow* m_window;
        StateManager* m_manager;
        LevelEditorMenu* m_levelEditorMenu;

        std::string selectedTileFilename;
        bool selectionRespectsGrid;
        std::vector<std::pair<sf::Vector2f, std::string> > sprites;
        bool enabledGrid;
        sf::RectangleShape grid[20][12];
        Player* player;
        bool justReselectedTile, justPlacedNewTile, movedCursorOutOfNewTile, testingLevelOut;
};


#endif // LEVELEDITORSTATE_HPP_INCLUDED
