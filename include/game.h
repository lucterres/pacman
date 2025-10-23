#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "pacman.h"
#include "ghost.h"
#include "maze.h"

typedef enum {
    MENU,
    PLAYING,
    GAME_OVER,
    WIN
} GameState;

class Game {
private:
    GameState state;
    Maze* maze;
    Pacman* pacman;
    Ghost* ghosts[4];
    int score;
    int highScore;
    bool isPaused;

public:
    Game();
    ~Game();
    
    void Init();
    void Update();
    void Draw();
    void HandleInput();
    void Reset();
    
    bool ShouldClose();
    GameState GetState() const { return state; }
};

#endif
