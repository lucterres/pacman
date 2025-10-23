#include "../include/collision.h"
#include "../include/pacman.h"
#include "../include/ghost.h"
#include "../include/maze.h"

void CollisionSystem::CheckPacmanGhostCollisions(Pacman* pacman, Ghost* ghosts[4], int& score) {
    if (!pacman->IsAlive()) return;
    
    Rectangle pacmanHitbox = pacman->GetHitbox();
    
    for (int i = 0; i < 4; i++) {
        Rectangle ghostHitbox = ghosts[i]->GetHitbox();
        
        if (CheckCollision(pacmanHitbox, ghostHitbox)) {
            if (pacman->IsSuperMode() && ghosts[i]->IsVulnerable()) {
                // Pacman come o fantasma
                ghosts[i]->SetMode(EATEN);
                score += 200;
            } else if (ghosts[i]->GetMode() != EATEN && ghosts[i]->GetMode() != FRIGHTENED) {
                // Fantasma pega o Pacman
                pacman->LoseLife();
                
                // Reset posições
                Vector2 startPos = {14.0f * TILE_SIZE + TILE_SIZE/2, 
                                   23.0f * TILE_SIZE + TILE_SIZE/2};
                pacman->Reset(startPos);
                
                for (int j = 0; j < 4; j++) {
                    ghosts[j]->Reset();
                }
            }
        }
    }
}

void CollisionSystem::CheckPacmanMazeCollisions(Pacman* pacman, Maze* maze, int& score) {
    Vector2 pacmanPos = pacman->GetPosition();
    Vector2 gridPos = maze->WorldToGrid(pacmanPos);
    
    TileType tile = maze->GetTile((int)gridPos.x, (int)gridPos.y);
    
    if (tile == DOT) {
        maze->CollectDot((int)gridPos.x, (int)gridPos.y);
        score += 10;
    } else if (tile == POWER_PELLET) {
        maze->CollectDot((int)gridPos.x, (int)gridPos.y);
        score += 50;
        pacman->ActivateSuperMode();
    }
}

bool CollisionSystem::CheckCollision(Rectangle rect1, Rectangle rect2) {
    return CheckCollisionRecs(rect1, rect2);
}
