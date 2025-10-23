# Pacman - C++ com Raylib

Implementação do clássico jogo Pacman desenvolvido em C++ utilizando a biblioteca raylib.

## Características

- ✅ Labirinto clássico do Pacman
- ✅ 4 fantasmas com IAs distintas (Blinky, Pinky, Inky, Clyde)
- ✅ Sistema de pontuação
- ✅ Power pellets e super mode
- ✅ Sistema de vidas
- ✅ Detecção de colisões

## Compilação

### Requisitos
- Compilador C++ (MinGW/g++ ou MSVC)
- CMake 3.15+
- Raylib 5.0 (incluído no projeto)

### Build com CMake

```powershell
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

## Execução

```powershell
.\bin\pacman.exe
```

## Controles

- **WASD** ou **Setas**: Mover o Pacman
- **P** ou **ESC**: Pausar
- **ENTER**: Iniciar jogo / Jogar novamente

## Estrutura do Projeto

```
pacman/
├── src/                  # Código fonte (.cpp)
├── include/              # Cabeçalhos (.h)
├── bin/                  # Executável
├── build/                # Arquivos de build
└── raylib-5.0_win64_mingw-w64/  # Biblioteca raylib
```

## Tecnologias

- C++17
- Raylib 5.0
- CMake

---

Desenvolvido seguindo as melhores práticas de Engenharia de Software.
