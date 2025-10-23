#include "../include/ghost.h"
#include "../include/maze.h"
#include "../include/pacman.h"
#include <cmath>
#include <cstdlib>

Ghost::Ghost() {
    mode = SCATTER;
    speed = GHOST_SPEED;
    direction = {1, 0};
    modeTimer = 0.0f;
    animTimer = 0.0f;
    animFrame = false;
}

Ghost::Ghost(GhostType ghostType, Vector2 startPos, Vector2 corner) {
    type = ghostType;
    position = startPos;
    startPosition = startPos;
    homeCorner = corner;
    mode = SCATTER;
    speed = GHOST_SPEED;
    direction = {1, 0};
    target = corner;
    modeTimer = 7.0f;
    animTimer = 0.0f;
    animFrame = false;
    color = GetGhostColor();
}

Ghost::~Ghost() {
}

void Ghost::Update(float deltaTime, Maze* maze, Pacman* pacman, Ghost* blinky) {
    // Atualizar timer de modo
    modeTimer -= deltaTime;
    if (modeTimer <= 0.0f) {
        if (mode == SCATTER) {
            SetMode(CHASE);
            modeTimer = 20.0f;
        } else if (mode == CHASE) {
            SetMode(SCATTER);
            modeTimer = 7.0f;
        } else if (mode == FRIGHTENED) {
            SetMode(SCATTER);
            modeTimer = 7.0f;
        }
    }
    
    // Atualizar animação
    UpdateAnimation(deltaTime);
    
    // Atualizar alvo baseado no modo e tipo
    UpdateTarget(pacman, blinky);
    
    // Mover fantasma
    UpdateMovement(deltaTime, maze);
}

void Ghost::Draw() {
    Color drawColor;
    
    if (mode == FRIGHTENED) {
        drawColor = DARKBLUE;
    } else if (mode == EATEN) {
        drawColor = WHITE;
    } else {
        drawColor = color;
    }
    
    // Corpo do fantasma (círculo + retângulo)
    DrawCircle(position.x, position.y - TILE_SIZE * 0.3f, TILE_SIZE * 0.7f, drawColor);
    DrawRectangle(position.x - TILE_SIZE * 0.7f, position.y - TILE_SIZE * 0.3f,
                  TILE_SIZE * 1.4f, TILE_SIZE * 0.8f, drawColor);
    
    // Ondulações na base
    for (int i = 0; i < 3; i++) {
        float x = position.x - TILE_SIZE * 0.7f + i * TILE_SIZE * 0.47f;
        DrawCircle(x + TILE_SIZE * 0.23f, position.y + TILE_SIZE * 0.5f, 
                   TILE_SIZE * 0.25f, drawColor);
    }
    
    // Olhos
    if (mode != EATEN) {
        DrawCircle(position.x - TILE_SIZE * 0.3f, position.y - TILE_SIZE * 0.2f, 
                   TILE_SIZE * 0.2f, WHITE);
        DrawCircle(position.x + TILE_SIZE * 0.3f, position.y - TILE_SIZE * 0.2f, 
                   TILE_SIZE * 0.2f, WHITE);
        
        // Pupilas
        DrawCircle(position.x - TILE_SIZE * 0.3f + direction.x * 3, 
                   position.y - TILE_SIZE * 0.2f + direction.y * 3, 
                   TILE_SIZE * 0.1f, BLUE);
        DrawCircle(position.x + TILE_SIZE * 0.3f + direction.x * 3, 
                   position.y - TILE_SIZE * 0.2f + direction.y * 3, 
                   TILE_SIZE * 0.1f, BLUE);
    }
}

void Ghost::SetMode(GhostMode newMode) {
    if (mode != newMode) {
        mode = newMode;
        
        // Reverter direção ao mudar de modo (exceto para EATEN)
        if (mode != EATEN) {
            direction.x = -direction.x;
            direction.y = -direction.y;
        }
        
        // Ajustar velocidade
        switch (mode) {
            case FRIGHTENED:
                speed = GHOST_FRIGHTENED_SPEED;
                break;
            case EATEN:
                speed = GHOST_EATEN_SPEED;
                break;
            default:
                speed = GHOST_SPEED;
                break;
        }
    }
}

void Ghost::Reset() {
    position = startPosition;
    direction = {1, 0};
    mode = SCATTER;
    speed = GHOST_SPEED;
    modeTimer = 7.0f;
}

Rectangle Ghost::GetHitbox() const {
    return {position.x - TILE_SIZE/2, position.y - TILE_SIZE/2,
            TILE_SIZE, TILE_SIZE};
}

void Ghost::UpdateTarget(Pacman* pacman, Ghost* blinky) {
    Vector2 pacmanPos = pacman->GetPosition();
    
    switch (mode) {
        case SCATTER:
            target = homeCorner;
            break;
            
        case CHASE:
            // IA simplificada - cada fantasma tem seu comportamento
            switch (type) {
                case BLINKY:  // Perseguição direta
                    target = pacmanPos;
                    break;
                    
                case PINKY:   // Mira à frente do Pacman (simplificado)
                    target.x = pacmanPos.x + (rand() % 3 - 1) * TILE_SIZE * 4;
                    target.y = pacmanPos.y + (rand() % 3 - 1) * TILE_SIZE * 4;
                    break;
                    
                case INKY:    // Movimento mais errático
                    target.x = pacmanPos.x + (rand() % 5 - 2) * TILE_SIZE * 2;
                    target.y = pacmanPos.y + (rand() % 5 - 2) * TILE_SIZE * 2;
                    break;
                    
                case CLYDE:   // Persegue se longe, foge se perto
                    float dist = sqrt(pow(position.x - pacmanPos.x, 2) + 
                                    pow(position.y - pacmanPos.y, 2));
                    if (dist > TILE_SIZE * 8) {
                        target = pacmanPos;
                    } else {
                        target = homeCorner;
                    }
                    break;
            }
            break;
            
        case FRIGHTENED:
            // Movimento aleatório
            if (rand() % 20 == 0) {
                target.x = (rand() % MAZE_WIDTH) * TILE_SIZE;
                target.y = (rand() % MAZE_HEIGHT) * TILE_SIZE;
            }
            break;
            
        case EATEN:
            target = startPosition;
            // Voltar ao modo scatter quando chegar
            if (fabs(position.x - startPosition.x) < TILE_SIZE &&
                fabs(position.y - startPosition.y) < TILE_SIZE) {
                SetMode(SCATTER);
            }
            break;
    }
}

void Ghost::UpdateMovement(float deltaTime, Maze* maze) {
    // IA simplificada: mover em direção ao alvo
    Vector2 diff = {target.x - position.x, target.y - position.y};
    float dist = sqrt(diff.x * diff.x + diff.y * diff.y);
    
    if (dist > 0) {
        // Escolher direção a cada frame (simplificado)
        ChooseDirection(maze);
        
        // Mover
        Vector2 newPos = {
            position.x + direction.x * speed * deltaTime,
            position.y + direction.y * speed * deltaTime
        };
        
        if (CanMove(newPos, maze)) {
            position = newPos;
        }
    }
    
    // Wrap around
    if (position.x < 0) position.x = MAZE_WIDTH * TILE_SIZE;
    if (position.x > MAZE_WIDTH * TILE_SIZE) position.x = 0;
}

void Ghost::ChooseDirection(Maze* maze) {
    // Decisão simplificada: tentar mover em direção ao alvo
    Vector2 diff = {target.x - position.x, target.y - position.y};
    
    Vector2 directions[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    float bestDist = 999999.0f;
    Vector2 bestDir = direction;
    
    for (int i = 0; i < 4; i++) {
        // Não reverter direção
        if (directions[i].x == -direction.x && directions[i].y == -direction.y)
            continue;
            
        Vector2 testPos = {
            position.x + directions[i].x * TILE_SIZE,
            position.y + directions[i].y * TILE_SIZE
        };
        
        if (!maze->IsWall(testPos)) {
            float dist = sqrt(pow(testPos.x - target.x, 2) + 
                            pow(testPos.y - target.y, 2));
            
            if (mode == FRIGHTENED) {
                // No modo assustado, escolher aleatoriamente
                if (rand() % 4 == 0) {
                    bestDir = directions[i];
                    break;
                }
            } else {
                if (dist < bestDist) {
                    bestDist = dist;
                    bestDir = directions[i];
                }
            }
        }
    }
    
    direction = bestDir;
}

bool Ghost::CanMove(Vector2 newPos, Maze* maze) {
    // Fantasmas podem passar pela casa dos fantasmas no modo EATEN
    if (mode == EATEN) {
        TileType tile = maze->GetTile(newPos);
        return tile != WALL;
    }
    
    return !maze->IsWall(newPos);
}

Color Ghost::GetGhostColor() {
    switch (type) {
        case BLINKY: return RED;
        case PINKY: return PINK;
        case INKY: return SKYBLUE;
        case CLYDE: return ORANGE;
        default: return WHITE;
    }
}

void Ghost::UpdateAnimation(float deltaTime) {
    animTimer += deltaTime * 8.0f;
    if (animTimer >= 1.0f) {
        animTimer = 0.0f;
        animFrame = !animFrame;
    }
}
