#include "Defines.hpp"
#include "Game.hpp"
#include <iostream>

int main(int argc, char** argv) {
    Game* game = new Game();

    if (!game->setup()) {
        std::cout << "Setup failed." << std::endl;
        return 1;
    }
    while (!game->isClosed()) {
        while(game->isRunning()) {
            game->render();
            game->input();
            game->update();
        }
        game->doAfterGame();
    }
    game->close();

    return 0;
}
