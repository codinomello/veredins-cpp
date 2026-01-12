# CMakeLists.txt - Veredins
cmake_minimum_required(VERSION 3.15)
project(veredins LANGUAGES CXX)

# Configurações do C++
set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# Build type padrão = Release (pode ser sobrescrito via -DCMAKE_BUILD_TYPE=Debug)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Raylib - configurações como subdiretório
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

# Raylib como subdiretório (recomendado: include/raylib)
add_subdirectory(include/raylib)

# Arquivos fonte
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executável principal
add_executable(veredins ${SOURCES})

# Includes
target_include_directories(veredins PRIVATE src include/raylib/src)

# Linking com raylib
target_link_libraries(veredins PRIVATE raylib)

# Definições (defines) - caminho dos assets
target_compile_definitions(veredins PRIVATE
    VEREDINS_ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/"
)

# Flags de compilação - warnings fortes (compatível GCC/Clang + MSVC)
if(MSVC)
    target_compile_options(veredins PRIVATE 
        W3
    )
else()
    target_compile_options(veredins PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow
    )
endif()

target_compile_options(veredins PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-O0 -g>
)

# Gera compile_commands.json (útil para clangd, LSP, neovim, etc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Opcional: propriedades do target (nome, pastas de saída)
set_target_properties(veredins PROPERTIES
    OUTPUT_NAME "veredins"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)