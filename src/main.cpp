#include "../include/game.h"

int main() {
    Game game;
    game.Init();
    
    while (!game.ShouldClose()) {
        game.HandleInput();
        game.Update();
        game.Draw();
    }
    
    return 0;
}
