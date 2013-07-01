#ifndef INLINEFUNCTIONS_HPP_INCLUDED
#define INLINEFUNCTIONS_HPP_INCLUDED

#include <string>

#include <SFML\Graphics.hpp>

enum GameStates
{
    GAME_STATE_NULL,
    GAME_STATE_INTRO,
    GAME_STATE_MENU,
    GAME_STATE_OPTIONS,
    GAME_STATE_LEVEL_SELECTION,
    GAME_STATE_GAME,
    GAME_STATE_LEVEL_EDITOR,
    GAME_STATE_EXIT
};

inline float GetDistance(float x1, float y1, float x2, float y2)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    float dist = sqrt((dx * dx) + (dy * dy));
    return (dist > 0 ? dist : 0);
}

inline bool IsInRange(float currX, float xDest, float currY, float yDest, float distance)
{
    return ((currX < xDest - distance && currX > xDest + distance && currY < yDest - distance && currY > yDest + distance) ||
            (currX > xDest - distance && currX < xDest + distance && currY > yDest - distance && currY < yDest + distance));
}

inline int urand(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}

inline bool WillCollision(float x1, float y1, float h1, float w1, float x2, float y2, float h2, float w2)
{
    return !(y1 >= y2 + h2 || x1 >= x2 + w2 || y1 + h1 <= y2 || x1 + w1 <= x2);
}

struct SpriteInfo
{
    std::string filename;
    sf::Vector2f position;
    bool isCollidable;
    bool forceIgnoreGrid;
    bool priorityInDrawing; //! NYI! When set to true it is drawn last (right before player, of course) 

    bool operator == (SpriteInfo spriteInfo)
    {
        return spriteInfo.filename == filename && spriteInfo.position == position && spriteInfo.isCollidable == isCollidable && spriteInfo.forceIgnoreGrid == forceIgnoreGrid && spriteInfo.priorityInDrawing == priorityInDrawing;
    }

    bool operator != (SpriteInfo spriteInfo)
    {
        return spriteInfo.filename != filename || spriteInfo.position != position || spriteInfo.isCollidable != isCollidable || spriteInfo.forceIgnoreGrid != forceIgnoreGrid || spriteInfo.priorityInDrawing != priorityInDrawing;
    }
};

#endif // INLINEFUNCTIONS_HPP_INCLUDED
