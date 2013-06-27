#pragma once

#include <vector>

class Game
{
    public:
        static Game& instance()
        {
            static Game game;
            return game;
        }

        int Update();

    private:
        Game();
        ~Game();
};

#define sGame Game::instance()
