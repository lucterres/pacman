#include "../include/maze.h"
#include <cstring>

Maze::Maze() {
    dotsCollected = 0;
    totalDots = 0;
    dotAnimTimer = 0.0f;
}

Maze::~Maze() {
}

void Maze::Init() {
    // Labirinto simplificado do Pacman (28x31)
    int layout[MAZE_HEIGHT][MAZE_WIDTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
        {1,3,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,3,1},
        {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
        {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
        {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
        {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
        {1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1},
        {1,1,1,1,1,1,2,1,1,1,1,1,0,1,1,0,1,1,1,1,1,2,1,1,1,1,1,1},
        {1,1,1,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,1},
        {1,1,1,1,1,1,2,1,1,0,1,1,1,4,4,1,1,1,0,1,1,2,1,1,1,1,1,1},
        {1,1,1,1,1,1,2,1,1,0,1,4,4,4,4,4,4,1,0,1,1,2,1,1,1,1,1,1},
        {0,0,0,0,0,0,2,0,0,0,1,4,4,4,4,4,4,1,0,0,0,2,0,0,0,0,0,0},
        {1,1,1,1,1,1,2,1,1,0,1,4,4,4,4,4,4,1,0,1,1,2,1,1,1,1,1,1},
        {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1},
        {1,1,1,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,1},
        {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1},
        {1,1,1,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,1,1,1},
        {1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
        {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
        {1,3,2,2,1,1,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,1,1,2,2,3,1},
        {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
        {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
        {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
        {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
        {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
        {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    
    memcpy(grid, layout, sizeof(grid));
    
    // Contar dots
    totalDots = 0;
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            if (grid[y][x] == DOT || grid[y][x] == POWER_PELLET) {
                totalDots++;
            }
        }
    }
    dotsCollected = 0;
}

void Maze::Draw() {
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            Vector2 pos = GridToWorld(x, y);
            
            switch (grid[y][x]) {
                case WALL:
                    DrawRectangle(pos.x, pos.y, TILE_SIZE, TILE_SIZE, BLUE);
                    break;
                case DOT:
                    DrawCircle(pos.x + TILE_SIZE/2, pos.y + TILE_SIZE/2, 2, WHITE);
                    break;
                case POWER_PELLET:
                    DrawCircle(pos.x + TILE_SIZE/2, pos.y + TILE_SIZE/2, 5, WHITE);
                    break;
                case GHOST_HOUSE:
                    DrawRectangle(pos.x, pos.y, TILE_SIZE, TILE_SIZE, DARKBLUE);
                    break;
            }
        }
    }
}

void Maze::Update(float deltaTime) {
    dotAnimTimer += deltaTime;
}

bool Maze::IsWall(int x, int y) {
    if (x < 0 || x >= MAZE_WIDTH || y < 0 || y >= MAZE_HEIGHT)
        return true;
    return grid[y][x] == WALL;
}

bool Maze::IsWall(Vector2 pos) {
    Vector2 gridPos = WorldToGrid(pos);
    return IsWall((int)gridPos.x, (int)gridPos.y);
}

TileType Maze::GetTile(int x, int y) {
    if (x < 0 || x >= MAZE_WIDTH || y < 0 || y >= MAZE_HEIGHT)
        return WALL;
    return (TileType)grid[y][x];
}

TileType Maze::GetTile(Vector2 pos) {
    Vector2 gridPos = WorldToGrid(pos);
    return GetTile((int)gridPos.x, (int)gridPos.y);
}

void Maze::CollectDot(int x, int y) {
    if (x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT) {
        if (grid[y][x] == DOT || grid[y][x] == POWER_PELLET) {
            grid[y][x] = EMPTY;
            dotsCollected++;
        }
    }
}

void Maze::CollectDot(Vector2 pos) {
    Vector2 gridPos = WorldToGrid(pos);
    CollectDot((int)gridPos.x, (int)gridPos.y);
}

Vector2 Maze::GridToWorld(int x, int y) {
    return {(float)(x * TILE_SIZE), (float)(y * TILE_SIZE)};
}

Vector2 Maze::WorldToGrid(Vector2 pos) {
    return {pos.x / TILE_SIZE, pos.y / TILE_SIZE};
}
