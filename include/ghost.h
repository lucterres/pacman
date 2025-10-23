#ifndef GHOST_H
#define GHOST_H

#include "raylib.h"

#define GHOST_SPEED 75.0f
#define GHOST_FRIGHTENED_SPEED 40.0f
#define GHOST_EATEN_SPEED 160.0f

typedef enum {
    CHASE,
    SCATTER,
    FRIGHTENED,
    EATEN
} GhostMode;

typedef enum {
    BLINKY,  // Vermelho
    PINKY,   // Rosa
    INKY,    // Azul
    CLYDE    // Laranja
} GhostType;

class Maze;
class Pacman;

class Ghost {
private:
    Vector2 position;
    Vector2 direction;
    Vector2 target;
    Vector2 homeCorner;
    Vector2 startPosition;
    float speed;
    GhostMode mode;
    GhostType type;
    Color color;
    float modeTimer;
    float animTimer;
    bool animFrame;

public:
    Ghost();
    Ghost(GhostType ghostType, Vector2 startPos, Vector2 corner);
    ~Ghost();
    
    void Update(float deltaTime, Maze* maze, Pacman* pacman, Ghost* blinky = nullptr);
    void Draw();
    
    void SetMode(GhostMode newMode);
    void Reset();
    
    Vector2 GetPosition() const { return position; }
    Rectangle GetHitbox() const;
    GhostMode GetMode() const { return mode; }
    bool IsVulnerable() const { return mode == FRIGHTENED; }
    
private:
    void UpdateTarget(Pacman* pacman, Ghost* blinky);
    void UpdateMovement(float deltaTime, Maze* maze);
    void ChooseDirection(Maze* maze);
    bool CanMove(Vector2 newPos, Maze* maze);
    Color GetGhostColor();
    void UpdateAnimation(float deltaTime);
};

#endif
