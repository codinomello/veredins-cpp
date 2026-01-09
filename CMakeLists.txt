cmake_minimum_required(VERSION 3.10)

project(veredins LANGUAGES CXX)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type padrão = Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Raylib como subdiretório (estático, sem exemplos)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
add_subdirectory(tools/raylib)

# Pega todos os .cpp em src/ e subpastas
file(GLOB_RECURSE SOURCES src/*.cpp)

# Executável
add_executable(veredins ${SOURCES})

# Includes
target_include_directories(veredins PRIVATE
    src
    tools/raylib/src
)

# Linka raylib
target_link_libraries(veredins PRIVATE raylib)

# Warnings fortes
target_compile_options(veredins PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow
)

# Otimizações por build type
target_compile_options(veredins PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-O0 -g>
)

# Caminho dos assets
target_compile_definitions(veredins PRIVATE
    VEREDINS_ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/"
)

# Gera compile_commands.json (para LSP, clangd, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)