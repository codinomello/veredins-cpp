cmake_minimum_required(VERSION 3.20)
project(veredins VERSION 0.1.0 LANGUAGES CXX)

# C++ settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type padrão
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependências
find_package(raylib CONFIG REQUIRED)

# Fontes (liste manualmente - adicione os seus .cpp aqui)
file(GLOB_RECURSE VEREDINS_SOURCES
    src/*.cpp
)

add_executable(veredins ${VEREDINS_SOURCES})

# Includes (src/ como root → #include "game/elements/element.h" funciona)
target_include_directories(veredins PRIVATE src)

# Link raylib
target_link_libraries(veredins PRIVATE raylib)

# Define path de assets
target_compile_definitions(veredins PRIVATE
    VEREDINS_ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/"
)

# Warnings & flags
if(MSVC)
    target_compile_options(veredins PRIVATE /W3)
else()
    target_compile_options(veredins PRIVATE
        -Wall -Wextra -Wpedantic
        -Wconversion -Wsign-conversion -Wshadow
    )
endif()

target_compile_options(veredins PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-O0 -g>
)

# Output
set_target_properties(veredins PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)