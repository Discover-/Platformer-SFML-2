#include "game.hpp"

int main()
{
    StateManager manager;
    manager.set_next_state(GAME_STATE_MENU);
    manager.start();
}
