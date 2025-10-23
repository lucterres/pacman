#include "../include/game.h"
#include "../include/collision.h"
#include <cstdio>

Game::Game() {
    state = MENU;
    maze = nullptr;
    pacman = nullptr;
    for (int i = 0; i < 4; i++) {
        ghosts[i] = nullptr;
    }
    score = 0;
    highScore = 0;
    isPaused = false;
}

Game::~Game() {
    if (maze) delete maze;
    if (pacman) delete pacman;
    for (int i = 0; i < 4; i++) {
        if (ghosts[i]) delete ghosts[i];
    }
}

void Game::Init() {
    const int screenWidth = MAZE_WIDTH * TILE_SIZE;
    const int screenHeight = MAZE_HEIGHT * TILE_SIZE + 40;
    
    InitWindow(screenWidth, screenHeight, "Pacman - C++ com Raylib");
    SetTargetFPS(60);
    
    // Criar objetos do jogo
    maze = new Maze();
    maze->Init();
    
    Vector2 pacmanStart = {MAZE_WIDTH * TILE_SIZE / 2.0f, 
                           (MAZE_HEIGHT - 5) * TILE_SIZE};
    pacman = new Pacman();
    pacman->Init(pacmanStart);
    
    // Criar fantasmas
    ghosts[0] = new Ghost(BLINKY, {13 * TILE_SIZE, 11 * TILE_SIZE}, 
                         {25 * TILE_SIZE, 0});
    ghosts[1] = new Ghost(PINKY, {14 * TILE_SIZE, 14 * TILE_SIZE}, 
                         {2 * TILE_SIZE, 0});
    ghosts[2] = new Ghost(INKY, {12 * TILE_SIZE, 14 * TILE_SIZE}, 
                         {27 * TILE_SIZE, 30 * TILE_SIZE});
    ghosts[3] = new Ghost(CLYDE, {15 * TILE_SIZE, 14 * TILE_SIZE}, 
                         {0, 30 * TILE_SIZE});
    
    state = PLAYING;
    score = 0;
}

void Game::Update() {
    if (state == PLAYING && !isPaused) {
        float deltaTime = GetFrameTime();
        
        // Atualizar objetos
        pacman->Update(deltaTime, maze);
        
        for (int i = 0; i < 4; i++) {
            ghosts[i]->Update(deltaTime, maze, pacman, ghosts[0]);
        }
        
        maze->Update(deltaTime);
        
        // Verificar colisões
        CollisionSystem::CheckPacmanMazeCollisions(pacman, maze, score);
        CollisionSystem::CheckPacmanGhostCollisions(pacman, ghosts, score);
        
        // Verificar condições de vitória/derrota
        if (maze->AllDotsCollected()) {
            state = WIN;
        }
        
        if (!pacman->IsAlive()) {
            state = GAME_OVER;
            if (score > highScore) {
                highScore = score;
            }
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    
    if (state == MENU) {
        DrawText("PACMAN", 200, 200, 60, YELLOW);
        DrawText("Pressione ENTER para iniciar", 150, 300, 20, WHITE);
        DrawText("Use WASD ou Setas para mover", 130, 350, 20, WHITE);
    }
    else if (state == PLAYING) {
        // Desenhar jogo
        maze->Draw();
        pacman->Draw();
        
        for (int i = 0; i < 4; i++) {
            ghosts[i]->Draw();
        }
        
        // HUD
        DrawText(TextFormat("Score: %d", score), 10, MAZE_HEIGHT * TILE_SIZE + 5, 20, WHITE);
        DrawText(TextFormat("Lives: %d", pacman->GetLives()), 
                 MAZE_WIDTH * TILE_SIZE - 120, MAZE_HEIGHT * TILE_SIZE + 5, 20, WHITE);
        
        if (pacman->IsSuperMode()) {
            DrawText("SUPER MODE!", MAZE_WIDTH * TILE_SIZE / 2 - 80, 
                    MAZE_HEIGHT * TILE_SIZE + 5, 20, ORANGE);
        }
        
        if (isPaused) {
            DrawRectangle(0, 0, MAZE_WIDTH * TILE_SIZE, 
                         MAZE_HEIGHT * TILE_SIZE + 40, Fade(BLACK, 0.5f));
            DrawText("PAUSADO", MAZE_WIDTH * TILE_SIZE / 2 - 100, 
                    MAZE_HEIGHT * TILE_SIZE / 2, 40, WHITE);
        }
    }
    else if (state == GAME_OVER) {
        DrawText("GAME OVER", 200, 250, 50, RED);
        DrawText(TextFormat("Score Final: %d", score), 200, 320, 25, WHITE);
        DrawText(TextFormat("High Score: %d", highScore), 200, 360, 25, YELLOW);
        DrawText("Pressione ENTER para jogar novamente", 100, 420, 20, WHITE);
    }
    else if (state == WIN) {
        DrawText("VOCE VENCEU!", 180, 250, 50, GREEN);
        DrawText(TextFormat("Score Final: %d", score), 200, 320, 25, WHITE);
        DrawText("Pressione ENTER para jogar novamente", 100, 380, 20, WHITE);
    }
    
    EndDrawing();
}

void Game::HandleInput() {
    if (state == MENU || state == GAME_OVER || state == WIN) {
        if (IsKeyPressed(KEY_ENTER)) {
            Reset();
        }
    }
    else if (state == PLAYING) {
        pacman->HandleInput();
        
        if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) {
            isPaused = !isPaused;
        }
    }
}

void Game::Reset() {
    // Resetar labirinto
    maze->Init();
    
    // Resetar Pacman
    Vector2 pacmanStart = {MAZE_WIDTH * TILE_SIZE / 2.0f, 
                           (MAZE_HEIGHT - 5) * TILE_SIZE};
    pacman->Init(pacmanStart);
    
    // Resetar fantasmas
    for (int i = 0; i < 4; i++) {
        ghosts[i]->Reset();
    }
    
    score = 0;
    isPaused = false;
    state = PLAYING;
}

bool Game::ShouldClose() {
    return WindowShouldClose();
}
