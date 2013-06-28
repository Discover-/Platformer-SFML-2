#include "game.hpp"

int main()
{
    StateManager manager;
    manager.set_next_state(StateManager::GameStates::STATE_MENU);
    manager.start();
}
