cmake_minimum_required(VERSION 3.15)
project(Pacman VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Raylib path
set(RAYLIB_PATH "${CMAKE_SOURCE_DIR}/raylib-5.0_win64_mingw-w64")
set(RAYLIB_INCLUDE_DIR "${RAYLIB_PATH}/include")
set(RAYLIB_LIB_DIR "${RAYLIB_PATH}/lib")

# Include directories
include_directories(${RAYLIB_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link directories
link_directories(${RAYLIB_LIB_DIR})

# Source files
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/maze.cpp
    src/pacman.cpp
    src/ghost.cpp
    src/collision.cpp
)

# Executable
add_executable(pacman ${SOURCES})

# Link libraries
target_link_libraries(pacman raylib opengl32 gdi32 winmm)

# Compiler flags
if(MSVC)
    target_compile_options(pacman PRIVATE /W4)
else()
    target_compile_options(pacman PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Output directory
set_target_properties(pacman PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
