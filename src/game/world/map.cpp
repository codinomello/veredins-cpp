#include <cmath>

#include "map.h"

void map_init(Map* m) {
    m->width = MAP_WIDTH;
    m->height = MAP_HEIGHT;

    for (i32 y = 0; y < MAP_HEIGHT; y++) {
        for (i32 x = 0; x < MAP_WIDTH; x++) {
            // base do mapa é grama
            m->tiles[y][x] = TILE_GRASS;

            // gera "lagos"
            f32 dist_to_center_lake = std::sqrt(std::pow(x - 10, 2) + std::pow(y - 10, 2));
            if (dist_to_center_lake < 5.0f) {
                m->tiles[y][x] = TILE_WATER;
            }

            // gera "caminhos de terra"
            if (std::abs(sinf(x * 0.2f) * 5.0f + 20.0f - y) < 2.0f) {
                m->tiles[y][x] = TILE_DIRT;
            }

            // bordas do mapa com rochas (obstáculos)
            if (x == 0 || y == 0 || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1) {
                m->tiles[y][x] = TILE_ROCK;
            }
            
            // algumas rochas aleatórias pelo mapa
            if (GetRandomValue(0, 100) > 98) {
                m->tiles[y][x] = TILE_ROCK;
            }
        }
    }
}

bool map_is_solid(const Map* map, int x, int y) {
    // proteção contra índices fora do mapa (Impede crash)
    if (x < 0 || x >= map->width || y < 0 || y >= map->height) {
        return true; // trata o "vazio" fora do mapa como parede
    }

    // pega o ladrilho naquela posição
    int tile = map->tiles[y][x]; 

    if (tile == 2 || tile == 3) {
        return true;
    }

    return false;
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