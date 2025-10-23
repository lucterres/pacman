#ifndef PACMAN_H
#define PACMAN_H

#include "raylib.h"

#define PACMAN_SPEED 80.0f
#define PACMAN_SUPER_SPEED 90.0f

class Maze;

class Pacman {
private:
    Vector2 position;
    Vector2 direction;
    Vector2 nextDirection;
    float speed;
    int lives;
    bool superMode;
    float superModeTimer;
    float animTimer;
    float mouthAngle;
    bool mouthOpening;

public:
    Pacman();
    ~Pacman();
    
    void Init(Vector2 startPos);
    void Update(float deltaTime, Maze* maze);
    void Draw();
    void HandleInput();
    
    void ActivateSuperMode();
    void LoseLife();
    void Reset(Vector2 startPos);
    
    Vector2 GetPosition() const { return position; }
    Rectangle GetHitbox() const;
    bool IsSuperMode() const { return superMode; }
    int GetLives() const { return lives; }
    bool IsAlive() const { return lives > 0; }
    
private:
    bool CanMove(Vector2 newPos, Maze* maze);
    void UpdateAnimation(float deltaTime);
};

#endif
