# =============================================================================
# CMakeLists.txt - Veredins
# =============================================================================

cmake_minimum_required(VERSION 3.10)
project(veredins LANGUAGES CXX)

# =============================================================================
# Configurações básicas do C++
# =============================================================================

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# Build type padrão = Release (pode ser sobrescrito via -DCMAKE_BUILD_TYPE=Debug)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# =============================================================================
# Raylib - configurações como subdiretório
# =============================================================================

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
add_subdirectory(include/raylib)

# =============================================================================
# Arquivos fonte
# =============================================================================

file(GLOB_RECURSE SOURCES "src/*.cpp")

# =============================================================================
# Executável principal
# =============================================================================

add_executable(veredins ${SOURCES})

# =============================================================================
# Includes
# =============================================================================

target_include_directories(veredins PRIVATE
    src
    include/raylib/src
)

# =============================================================================
# Linking com raylib
# =============================================================================

target_link_libraries(veredins PRIVATE raylib)

# =============================================================================
# Flags de compilação - warnings fortes (compatível GCC/Clang + MSVC)
# =============================================================================

if(MSVC)
    target_compile_options(veredins PRIVATE
        /W3           # Nível 4 de warnings (o mais próximo de -Wall -Wextra)
        /w14242       # Conversões implícitas possíveis perda de dados
        /w14254       # Operador diferente em tipos aritméticos
        /w14263       # Função não usa seu parâmetro
        /w14265       # Classe tem membros virtuais sem destrutor virtual
        /w14287       # Operador não é membro
        /we4289       # Variável não-constante declarada com inicializador
        /w14296       # Comparação unsigned/signed
        /w14311       # Ponteiro truncado
        /w14545       # Expressão antes da vírgula
        /w14546       # Função chamada antes da vírgula
        /w14547       # Operador antes da vírgula
        /w14549       # Operador antes da vírgula (com consequência diferente)
        /w14555       # Expressão tem efeito colateral
        /w14619       # Re-declaração de variável
        /w14640       # Inicializador de membro não está na ordem de declaração
        /w14826       # Conversão de tipo inteiro maior para menor
        /w14905       # Conversão de string literal para char*
        /w14906       # Conversão de string literal para wchar_t*
        /w14928       # Inicialização estática com cast
    )
else()
    target_compile_options(veredins PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wshadow
    )
endif()

target_compile_options(veredins PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-O0 -g>
)

# =============================================================================
# Definições (defines) - caminho dos assets
# =============================================================================

target_compile_definitions(veredins PRIVATE
    VEREDINS_ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/"
)

# =============================================================================
# Utilitários para desenvolvimento
# =============================================================================

# Gera compile_commands.json (útil para clangd, LSP, neovim, etc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# =============================================================================
# Opcional: propriedades do target (nome, pastas de saída)
# =============================================================================

set_target_properties(veredins PROPERTIES
    OUTPUT_NAME "veredins"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)