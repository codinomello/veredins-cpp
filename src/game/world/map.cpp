#include <cstdlib>

#include "map.h"

void map_init(Map* map) {
    map->width = 40;
    map->height = 23;
    map->tiles = (u8*)calloc(map->width * map->height, sizeof(u8));
}

void map_draw(const Map* map) {
    // grid do chão
    for (i32 y = -500; y < 1500; y += 50) {
        DrawLine(-500, y, 1500, y, ColorAlpha(DARKGRAY, 0.3f));
    }
    for (i32 x = -500; x < 1500; x += 50) {
        DrawLine(x, -500, x, 1500, ColorAlpha(DARKGRAY, 0.3f));
    }
}

bool map_is_solid(const Map* map, i32 tile_x, i32 tile_y) {
    if (tile_x < 0 || tile_x >= map->width || tile_y < 0 || tile_y >= map->height) {
        return true; // bordas são sólidas
    }
    return map->tiles[tile_y * map->width + tile_x] == 1;
}

void map_shutdown(Map* map) {
    if (map->tiles) {
        free(map->tiles);
        map->tiles = nullptr;
    }
}