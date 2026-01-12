#include "map.h"
#include "raylib.h"

#include "map.h"
#include <cmath> // Para usar sin/cos ou gerar padrões

void map_init(Map* m) {
    m->width = MAP_WIDTH;
    m->height = MAP_HEIGHT;

    for (i32 y = 0; y < MAP_HEIGHT; y++) {
        for (i32 x = 0; x < MAP_WIDTH; x++) {
            // 1. Base do mapa é grama
            m->tiles[y][x] = TILE_GRASS;

            // 2. Gerar "Lagos" (Círculos de água em posições específicas)
            f32 dist_to_center_lake = std::sqrt(std::pow(x - 10, 2) + std::pow(y - 10, 2));
            if (dist_to_center_lake < 5.0f) {
                m->tiles[y][x] = TILE_WATER;
            }

            // 3. Gerar "Caminhos de Terra" (Usando uma função de onda simples)
            if (std::abs(sinf(x * 0.2f) * 5.0f + 20.0f - y) < 2.0f) {
                m->tiles[y][x] = TILE_DIRT;
            }

            // 4. Bordas do mapa com rochas (obstáculos)
            if (x == 0 || y == 0 || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1) {
                m->tiles[y][x] = TILE_ROCK;
            }
            
            // 5. Algumas rochas aleatórias pelo mapa
            if (GetRandomValue(0, 100) > 98) {
                m->tiles[y][x] = TILE_ROCK;
            }
        }
    }
}

Color map_get_tile_color(Tile t) {
    switch (t) {
        case TILE_GRASS:
            return LIME;
        case TILE_DIRT:
            return BEIGE;
        case TILE_WATER:
            return BLUE;
        case TILE_ROCK:
            return DARKGRAY;
        default:
            return BLACK;
    }
}

void map_draw(const Map* m) {
    for (i32 y = 0; y < m->height; y++) {
        for (i32 x = 0; x < m->width; x++) {
            Color color = BLACK;
            color = map_get_tile_color(m->tiles[y][x]);
            DrawRectangle(
                x * TILE_SIZE,
                y * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE,
                color
            );
        }
    }
}