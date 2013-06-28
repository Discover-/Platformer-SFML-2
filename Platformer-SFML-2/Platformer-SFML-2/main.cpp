#include "game.h"

int main()
{
    StateManager manager;
    manager.set_next_state(StateManager::GameStates::STATE_GAME);
    manager.start();
}
