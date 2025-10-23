# Agente de Configuração - Projeto C++

## Diretivas Principais

    1. Apresente um plano e implemente somente apos minha aprovação
    2. Antes de criar todo o projeto faça um pequeno teste de compilação com o ambiente comfigurado
    3. Crie as estruturas de projeto e pastas necessárias. 
    4. Utilize as melhores práticas de Engenharia de Software na codificação 
    5. Não crie documentação excessiva, como arquivos Markdown ou de instalação. Gere apenas o código necessário para criar o aplicativo. 

## 🎯 Objetivo do Projeto

Implementação do clássico jogo Pacman desenvolvido em C utilizando a biblioteca raylib., seguindo boas práticas de programação e padrões modernos de C++.

---

## 🏗️ Estrutura de Diretórios

```
pacman/
├── src/                    # Código fonte
├── include/               # Arquivos de cabeçalho
├── tests/                 # Testes unitários
├── build/                 # Arquivos de build (gerado)
├── bin/                   # Executáveis (gerado)
├── docs/                  # Documentação
├── CMakeLists.txt        # Configuração CMake
├── README.md             # Documentação principal
├── .gitignore            # Arquivos ignorados pelo Git
└── agente.md             # Este arquivo
```

---

## 🔧 Configuração do Ambiente

**Biblioteca:** raylib (precisa ser instalada)

### Requisitos do Sistema

- **Compilador:** 
  - GCC 9.0+ / MinGW (Windows)
  - Clang 10.0+
  - MSVC 2019+ (Visual Studio)
  
- **Build System:** CMake 3.15+

- **Ferramentas Opcionais:**
  - Git para controle de versão
  - Doxygen para documentação
  - GTest para testes unitários

### Instalação no Windows

```powershell
# Instalar MinGW ou MSVC
# Instalar CMake: https://cmake.org/download/

# Verificar instalação
g++ --version
cmake --version
```

---

## 🚀 Comandos de Build

### Compilação Manual (g++)

```powershell
# Compilar arquivo único
g++ -std=c++17 src/main.cpp -o bin/calculadora.exe

# Compilar múltiplos arquivos
g++ -std=c++17 -I include src/*.cpp -o bin/calculadora.exe

# Com otimização
g++ -std=c++17 -O2 -I include src/*.cpp -o bin/calculadora.exe

# Com debug
g++ -std=c++17 -g -I include src/*.cpp -o bin/calculadora.exe
```

### Usando CMake

```powershell
# Criar diretório de build
mkdir build ; cd build

# Configurar projeto
cmake ..

# Compilar
cmake --build .

# Executar
.\bin\calculadora.exe
```

---

## 📝 Padrões de Código

### Convenções de Nomenclatura

- **Classes:** PascalCase (ex: `Calculator`, `MathUtils`)
- **Funções:** camelCase (ex: `calculateSum`, `getResult`)
- **Variáveis:** camelCase (ex: `userInput`, `resultValue`)
- **Constantes:** UPPER_SNAKE_CASE (ex: `MAX_VALUE`, `PI`)
- **Arquivos:** snake_case (ex: `calculator.cpp`, `math_utils.h`)

### Estilo de Código

```cpp
// Exemplo de estrutura recomendada
class Calculator {
private:
    double result;
    
public:
    Calculator();
    ~Calculator();
    
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    
    double getResult() const;
    void clearResult();
};
```

---



---

## 🧪 Testes

### Estrutura de Testes

```cpp
// Exemplo usando assertions simples
void testAddition() {
    Calculator calc;
    assert(calc.add(2, 3) == 5);
    assert(calc.add(-1, 1) == 0);
}

void testDivision() {
    Calculator calc;
    assert(calc.divide(10, 2) == 5);
    // Teste de divisão por zero
}
```

### Executar Testes

```powershell
# Compilar testes
g++ -std=c++17 -I include tests/test_calculator.cpp src/calculator.cpp -o bin/tests.exe

# Executar
.\bin\tests.exe
```

---

## 📚 Dependências

### Bibliotecas Padrão C++
- `<iostream>` - Entrada/saída
- `<cmath>` - Funções matemáticas
- `<string>` - Manipulação de strings
- `<vector>` - Containers dinâmicos
- `<stdexcept>` - Exceções

### Bibliotecas Externas (Opcionais)
- **Google Test** - Framework de testes
- **Boost** - Bibliotecas auxiliares
- **fmt** - Formatação moderna
  **raylib** - instalar

---

## 🐛 Tratamento de Erros

### Diretrizes

1. Usar exceções para erros críticos
2. Validar entradas do usuário
3. Tratar divisão por zero
4. Verificar overflow/underflow
5. Mensagens de erro claras e em português

```cpp
// Exemplo
double divide(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Erro: Divisão por zero não permitida!");
    }
    return a / b;
}
```

---

## 📖 Documentação

### Comentários no Código

```cpp
/**
 * @brief Realiza a adição de dois números
 * @param a Primeiro operando
 * @param b Segundo operando
 * @return Soma de a e b
 */
double add(double a, double b);
```

### Gerar Documentação

```powershell
# Usando Doxygen (se instalado)
doxygen Doxyfile
```

---

## 🔄 Controle de Versão

### Git Workflow

```powershell
# Inicializar repositório
git init

# Adicionar arquivos
git add .

# Commit inicial
git commit -m "feat: Initial project setup"

# Criar branch para nova feature
git checkout -b feature/advanced-operations
```

### Mensagens de Commit

- `feat:` Nova funcionalidade
- `fix:` Correção de bug
- `docs:` Documentação
- `style:` Formatação
- `refactor:` Refatoração
- `test:` Testes
- `chore:` Tarefas gerais

---

## 🔒 Segurança e Qualidade

### Checklist de Qualidade

- [ ] Código compila sem warnings
- [ ] Testes passam
- [ ] Sem memory leaks (usar valgrind ou sanitizers)
- [ ] Documentação atualizada
- [ ] Código revisado
- [ ] Performance aceitável

### Compilar com Warnings

```powershell
g++ -std=c++17 -Wall -Wextra -Werror -I include src/*.cpp -o bin/calculadora.exe
```

---

## 🎯 Metas de Desenvolvimento

### Curto Prazo (1-2 semanas)
- Implementar operações básicas
- Criar interface de console
- Adicionar testes básicos

### Médio Prazo (1 mês)
- Operações avançadas
- Sistema de histórico
- Melhorar interface

### Longo Prazo (3 meses)
- GUI (interface gráfica) opcional
- Plugin system
- Modo programador (hex, bin, oct)

---

## 📞 Suporte e Referências

### Documentação C++
- [cppreference.com](https://en.cppreference.com/)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/)
- [CMake Documentation](https://cmake.org/documentation/)

### Comunidade
- Stack Overflow
- Reddit: r/cpp
- Discord: C++ Brasil

---

## 📝 Notas do Agente

### Decisões de Design

1. **Linguagem:** C++17 escolhido por balancear modernidade e compatibilidade
2. **Arquitetura:** Separação clara entre lógica e interface
3. **Build System:** CMake para portabilidade multiplataforma

### Próximos Passos

1. Criar estrutura básica de diretórios
4. Adicionar CMakeLists.txt
5. Escrever README.md
6. Implementar testes

### Observações Importantes

- Sempre compilar com `-std=c++17` no mínimo
- Manter compatibilidade com Windows (PowerShell)
- Priorizar clareza sobre otimização prematura
- Documentar decisões importantes
- Manter código modular e testável

---
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

## 🔄 Histórico de Mudanças

| Data | Versão | Descrição |
|------|--------|-----------|
| 2025-10-17 | 1.0.0 | Criação inicial do documento de configuração |

---

**Última atualização:** 17 de Outubro de 2025  
**Mantido por:** Agente de Desenvolvimento C++
