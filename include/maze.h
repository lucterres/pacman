#ifndef MAZE_H
#define MAZE_H

#include "raylib.h"

#define MAZE_WIDTH 28
#define MAZE_HEIGHT 31
#define TILE_SIZE 20

typedef enum {
    EMPTY = 0,
    WALL = 1,
    DOT = 2,
    POWER_PELLET = 3,
    GHOST_HOUSE = 4
} TileType;

class Maze {
private:
    int grid[MAZE_HEIGHT][MAZE_WIDTH];
    int totalDots;
    int dotsCollected;
    float dotAnimTimer;

public:
    Maze();
    ~Maze();
    
    void Init();
    void Draw();
    void Update(float deltaTime);
    
    bool IsWall(int x, int y);
    bool IsWall(Vector2 pos);
    TileType GetTile(int x, int y);
    TileType GetTile(Vector2 pos);
    void CollectDot(int x, int y);
    void CollectDot(Vector2 pos);
    
    bool AllDotsCollected() const { return dotsCollected >= totalDots; }
    int GetDotsCollected() const { return dotsCollected; }
    
    Vector2 GridToWorld(int x, int y);
    Vector2 WorldToGrid(Vector2 pos);
};

#endif
