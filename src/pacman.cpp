#include "../include/pacman.h"
#include "../include/maze.h"
#include <cmath>

Pacman::Pacman() {
    lives = 3;
    speed = PACMAN_SPEED;
    superMode = false;
    superModeTimer = 0.0f;
    animTimer = 0.0f;
    mouthAngle = 0.0f;
    mouthOpening = true;
    direction = {0, 0};
    nextDirection = {0, 0};
}

Pacman::~Pacman() {
}

void Pacman::Init(Vector2 startPos) {
    position = startPos;
    direction = {0, 0};
    nextDirection = {0, 0};
    speed = PACMAN_SPEED;
    superMode = false;
    superModeTimer = 0.0f;
    animTimer = 0.0f;
    mouthAngle = 0.0f;
}

void Pacman::Update(float deltaTime, Maze* maze) {
    // Atualizar super mode
    if (superMode) {
        superModeTimer -= deltaTime;
        if (superModeTimer <= 0.0f) {
            superMode = false;
            speed = PACMAN_SPEED;
        }
    }
    
    // Atualizar animação
    UpdateAnimation(deltaTime);
    
    // Tentar mudar direção
    if (nextDirection.x != 0 || nextDirection.y != 0) {
        Vector2 testPos = {
            position.x + nextDirection.x * speed * deltaTime,
            position.y + nextDirection.y * speed * deltaTime
        };
        
        if (CanMove(testPos, maze)) {
            direction = nextDirection;
        }
    }
    
    // Mover na direção atual
    if (direction.x != 0 || direction.y != 0) {
        Vector2 newPos = {
            position.x + direction.x * speed * deltaTime,
            position.y + direction.y * speed * deltaTime
        };
        
        if (CanMove(newPos, maze)) {
            position = newPos;
        }
    }
    
    // Wrap around (teleporte nas bordas)
    if (position.x < 0) position.x = MAZE_WIDTH * TILE_SIZE;
    if (position.x > MAZE_WIDTH * TILE_SIZE) position.x = 0;
}

void Pacman::Draw() {
    float angle = 0;
    if (direction.x > 0) angle = 0;
    else if (direction.x < 0) angle = 180;
    else if (direction.y > 0) angle = 90;
    else if (direction.y < 0) angle = 270;
    
    Color color = superMode ? ORANGE : YELLOW;
    
    // Desenhar Pacman como círculo com boca
    DrawCircleSector(position, TILE_SIZE * 0.8f, angle + mouthAngle, 
                     angle + 360 - mouthAngle, 20, color);
}

void Pacman::HandleInput() {
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        nextDirection = {1, 0};
    }
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        nextDirection = {-1, 0};
    }
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        nextDirection = {0, 1};
    }
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        nextDirection = {0, -1};
    }
}

void Pacman::ActivateSuperMode() {
    superMode = true;
    superModeTimer = 8.0f;
    speed = PACMAN_SUPER_SPEED;
}

void Pacman::LoseLife() {
    lives--;
}

void Pacman::Reset(Vector2 startPos) {
    position = startPos;
    direction = {0, 0};
    nextDirection = {0, 0};
    superMode = false;
    speed = PACMAN_SPEED;
}

Rectangle Pacman::GetHitbox() const {
    return {position.x - TILE_SIZE/2, position.y - TILE_SIZE/2, 
            TILE_SIZE, TILE_SIZE};
}

bool Pacman::CanMove(Vector2 newPos, Maze* maze) {
    // Verificar os 4 cantos do Pacman
    float offset = TILE_SIZE * 0.4f;
    
    Vector2 corners[4] = {
        {newPos.x - offset, newPos.y - offset},
        {newPos.x + offset, newPos.y - offset},
        {newPos.x - offset, newPos.y + offset},
        {newPos.x + offset, newPos.y + offset}
    };
    
    for (int i = 0; i < 4; i++) {
        if (maze->IsWall(corners[i])) {
            return false;
        }
    }
    
    return true;
}

void Pacman::UpdateAnimation(float deltaTime) {
    animTimer += deltaTime * 10.0f;
    
    if (mouthOpening) {
        mouthAngle += deltaTime * 200.0f;
        if (mouthAngle >= 45.0f) {
            mouthAngle = 45.0f;
            mouthOpening = false;
        }
    } else {
        mouthAngle -= deltaTime * 200.0f;
        if (mouthAngle <= 0.0f) {
            mouthAngle = 0.0f;
            mouthOpening = true;
        }
    }
}
