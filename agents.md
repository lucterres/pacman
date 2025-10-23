# Agents - Sistema de Personagens do Pacman

## Diretivas Principais
    1.Apresente um plano e implemente somente apos minha aprovação
    2. Não crie documentação excessiva, como arquivos Markdown ou de instalação. Gere apenas o código necessário para criar o aplicativo. 
    3. Crie somente as estruturas de projeto e pastas necessárias. 
    4. Utilize as melhores práticas de Engenharia de Software na codificação 

## Visão Geral

Este documento descreve o sistema de agentes (personagens) do jogo Pacman desenvolvido em C com a biblioteca raylib. O jogo possui diferentes tipos de agentes com comportamentos únicos e inteligência artificial específica.

## Compilação do Projeto

**Biblioteca:** raylib (precisa ser instalada)

### Comando de Compilação
```bash
"C:\msys64\mingw64\bin\gcc.exe" -o pacman *.c -lraylib -lopengl32 -lgdi32 -lwinmm
```

## Tipos de Agentes

### 1. Pacman (Jogador)
- **Arquivo:** `pacman.c` / `pacman.h`
- **Controle:** Input do usuário (setas ou WASD)
- **Velocidade:** Base (modificável por power-ups)
- **Habilidades:**
  - Movimento em 4 direções
  - Coleta de dots e power pellets
  - Modo super após consumir power pellet

#### Estrutura de Dados
```c
typedef struct {
    Vector2 position;
    Vector2 direction;
    float speed;
    int score;
    int lives;
    bool superMode;
    float superModeTimer;
    Rectangle hitbox;
} Pacman;
```

### 2. Fantasmas (Ghost AI)

#### 2.1 Blinky (Fantasma Vermelho) - "Shadow"
- **Arquivo:** `blinky.c` / `blinky.h`
- **Comportamento:** Perseguição direta ao Pacman
- **Estratégia:** Caminho mais curto até a posição atual do Pacman
- **Velocidade:** 100% da velocidade base

#### 2.2 Pinky (Fantasma Rosa) - "Speedy"
- **Arquivo:** `pinky.c` / `pinky.h`
- **Comportamento:** Emboscada - mira 4 posições à frente do Pacman
- **Estratégia:** Antecipa o movimento do jogador
- **Velocidade:** 100% da velocidade base

#### 2.3 Inky (Fantasma Azul) - "Bashful"
- **Arquivo:** `inky.c` / `inky.h`
- **Comportamento:** Movimento baseado na posição de Blinky e Pacman
- **Estratégia:** Calcula vetor entre Blinky e duas posições à frente do Pacman
- **Velocidade:** 95% da velocidade base

#### 2.4 Clyde (Fantasma Laranja) - "Pokey"
- **Arquivo:** `clyde.c` / `clyde.h`
- **Comportamento:** Persegue quando longe, foge quando próximo
- **Estratégia:** Troca entre perseguição e patrulhamento do canto
- **Velocidade:** 95% da velocidade base

#### Estrutura Base dos Fantasmas
```c
typedef enum {
    CHASE,      // Perseguição
    SCATTER,    // Dispersão
    FRIGHTENED, // Assustado (modo azul)
    EATEN       // Comido (retornando à base)
} GhostMode;

typedef struct {
    Vector2 position;
    Vector2 direction;
    Vector2 target;
    Vector2 homeCorner;
    float speed;
    GhostMode mode;
    Color color;
    float modeTimer;
    Rectangle hitbox;
    bool isInHouse;
} Ghost;
```

## Sistema de IA dos Fantasmas

### Algoritmo de Pathfinding
- **Método:** A* (A-Star) modificado para grade do labirinto
- **Restrições:** Fantasmas não podem reverter direção (exceto ao mudar de modo)
- **Intersections:** Decisões tomadas apenas em cruzamentos

### Estados dos Fantasmas

#### 1. Scatter Mode (Dispersão)
- Fantasmas se dirigem aos seus cantos específicos
- Duração: 7 segundos nos primeiros níveis
- Frequência: Cicla com Chase Mode

#### 2. Chase Mode (Perseguição)
- Cada fantasma usa sua estratégia específica
- Duração: 20 segundos nos primeiros níveis
- Comportamento principal do jogo

#### 3. Frightened Mode (Assustado)
- Ativado quando Pacman come power pellet
- Fantasmas ficam azuis e vulneráveis
- Movimento pseudo-aleatório
- Duração: 6-10 segundos (diminui com o nível)

#### 4. Eaten Mode (Comido)
- Fantasma retorna rapidamente à casa central
- Apenas os olhos são visíveis
- Velocidade dobrada
- Regenera ao chegar na base

### Funções de Target (Alvo)

#### Blinky Target
```c
Vector2 GetBlinkyTarget(Pacman* pacman) {
    return pacman->position;
}
```

#### Pinky Target
```c
Vector2 GetPinkyTarget(Pacman* pacman) {
    Vector2 target = pacman->position;
    // 4 tiles à frente na direção atual
    target.x += pacman->direction.x * TILE_SIZE * 4;
    target.y += pacman->direction.y * TILE_SIZE * 4;
    return target;
}
```

#### Inky Target
```c
Vector2 GetInkyTarget(Pacman* pacman, Ghost* blinky) {
    Vector2 pacmanOffset;
    pacmanOffset.x = pacman->position.x + (pacman->direction.x * TILE_SIZE * 2);
    pacmanOffset.y = pacman->position.y + (pacman->direction.y * TILE_SIZE * 2);
    
    Vector2 target;
    target.x = pacmanOffset.x + (pacmanOffset.x - blinky->position.x);
    target.y = pacmanOffset.y + (pacmanOffset.y - blinky->position.y);
    return target;
}
```

#### Clyde Target
```c
Vector2 GetClydeTarget(Pacman* pacman, Ghost* clyde) {
    float distance = Vector2Distance(clyde->position, pacman->position);
    if (distance > TILE_SIZE * 8) {
        return pacman->position;  // Perseguir se longe
    } else {
        return clyde->homeCorner; // Fugir para canto se próximo
    }
}
```

## Sistema de Colisões

### Detecção de Colisão
```c
bool CheckCollision(Rectangle rect1, Rectangle rect2) {
    return CheckCollisionRecs(rect1, rect2);
}
```

### Tipos de Colisão
1. **Pacman vs Ghost (Normal):** Pacman perde vida
2. **Pacman vs Ghost (Super Mode):** Ghost é comido, pontos extras
3. **Agent vs Wall:** Movimento bloqueado
4. **Pacman vs Dot:** Coleta dot, pontos
5. **Pacman vs Power Pellet:** Ativa super mode

## Sistema de Animação

### Sprites dos Agentes
- **Pacman:** 3 frames por direção (abrir/fechar boca)
- **Fantasmas:** 2 frames por direção
- **Modo Assustado:** Sprite azul piscante quando próximo do fim
- **Olhos:** Sprite especial para fantasmas comidos

### Controle de Animação
```c
typedef struct {
    int currentFrame;
    int frameCount;
    float frameTimer;
    float frameSpeed;
} Animation;
```

## Configurações de Gameplay

### Velocidades (pixels por segundo)
- **Pacman Normal:** 80
- **Pacman Super Mode:** 90
- **Fantasmas Chase/Scatter:** 75
- **Fantasmas Frightened:** 40
- **Fantasmas Eaten:** 160

### Timings (segundos)
- **Power Pellet Duration:** 6-10 (decresce por nível)
- **Scatter Duration:** 7 (primeiros modos)
- **Chase Duration:** 20 (primeiros modos)
- **House Exit Delay:** 4 (Pinky), 17 (Inky), 32 (Clyde)

## Implementação Sugerida

### Arquivos do Projeto
```
/src
  ├── main.c              // Loop principal do jogo
  ├── game.c/.h           // Lógica geral do jogo
  ├── pacman.c/.h         // Jogador Pacman
  ├── ghost.c/.h          // Sistema base de fantasmas
  ├── blinky.c/.h         // IA específica do Blinky
  ├── pinky.c/.h          // IA específica do Pinky
  ├── inky.c/.h           // IA específica do Inky
  ├── clyde.c/.h          // IA específica do Clyde
  ├── pathfinding.c/.h    // Algoritmos de pathfinding
  ├── maze.c/.h           // Sistema do labirinto
  └── utils.c/.h          // Funções utilitárias

/assets
  ├── sprites/            // Sprites dos personagens
  ├── sounds/             // Efeitos sonoros
  └── fonts/              // Fontes do jogo
```

### Loop Principal Sugerido
```c
int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pacman");
    InitAudioDevice();
    
    // Inicializar agentes
    Pacman pacman = InitPacman();
    Ghost ghosts[4] = {
        InitBlinky(),
        InitPinky(), 
        InitInky(),
        InitClyde()
    };
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        // Update
        UpdatePacman(&pacman);
        UpdateGhosts(ghosts, &pacman);
        CheckCollisions(&pacman, ghosts);
        
        // Draw
        BeginDrawing();
        ClearBackground(BLACK);
        DrawMaze();
        DrawPacman(&pacman);
        DrawGhosts(ghosts);
        EndDrawing();
    }
    
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
```

## Considerações de Performance

### Otimizações Recomendadas
1. **Grid-based Movement:** Movimento baseado em grade para simplificar colisões
2. **Spatial Partitioning:** Dividir o mapa em setores para otimizar pathfinding
3. **State Caching:** Cache de estados de IA para evitar recálculos
4. **Sprite Batching:** Agrupar desenho de sprites similares

### Debugging
- Modo debug para visualizar targets dos fantasmas
- Display de estados de IA
- Hitbox visualization
- Performance metrics

## Recursos Adicionais

### Sons Recomendados
- Wakka wakka (movimento do Pacman)
- Siren (fantasmas perseguindo)
- Power pellet sound
- Ghost eaten sound
- Death sound
- Level start sound

### Extensões Futuras
- Power-ups adicionais
- Diferentes tipos de fantasmas
- Múltiplos labirintos
- Sistema de high scores
- Multiplayer local

---

**Última atualização:** Outubro 2025  
**Versão:** 1.0  
**Autor:** [Seu Nome]