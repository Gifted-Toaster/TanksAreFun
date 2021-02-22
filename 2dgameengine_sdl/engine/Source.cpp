#include "Constans.h"
#include "Game.h"

int main(int argc, char* args[]) {
    Game* game = new Game();

    // Initialize our game window
    game->Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, true);

    /*     
    Our main game loop
        While is running true:
            1) Process user input
            2) Update our assets
            3) Render our images
    */
    while (game->IsRunning()) {
        game->ProcessInput();
        game->Update();
        game->Render();
    }

    // Closing SDL when it's finished
    game->Destroy();

    return 0;
}
