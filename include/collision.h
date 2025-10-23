#ifndef COLLISION_H
#define COLLISION_H

#include "raylib.h"

class Pacman;
class Ghost;
class Maze;
class Game;

class CollisionSystem {
public:
    static void CheckPacmanGhostCollisions(Pacman* pacman, Ghost* ghosts[4], int& score);
    static void CheckPacmanMazeCollisions(Pacman* pacman, Maze* maze, int& score);
    static bool CheckCollision(Rectangle rect1, Rectangle rect2);
};

#endif
