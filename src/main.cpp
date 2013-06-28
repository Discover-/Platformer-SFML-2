#include "game.hpp"

int main()
{
    StateManager manager;
    manager.set_next_state(StateManager::GameStates::GAME_STATE_MENU);
    manager.start();
}
