#include "map.h"
#include "raylib.h"

void map_init(TileMap* map) {
    map->width = MAP_WIDTH;
    map->height = MAP_HEIGHT;

    for (i32 y = 0; y < MAP_HEIGHT; y++) {
        for (i32 x = 0; x < MAP_WIDTH; x++) {
            if (y > MAP_HEIGHT / 2) {
                map->tiles[y][x] = TILE_GRASS;
            } else {
                map->tiles[y][x] = TILE_DIRT;
            }
        }
    }
}

Color map_get_tile_color(u32 tile_type) {
    switch (tile_type) {
        case TILE_GRASS:
            return GREEN;
        case TILE_DIRT:
            return BROWN;
        case TILE_WATER:
            return BLUE;
        default:
            return MAGENTA; // Unknown tile type
    }
}

void map_draw(const TileMap* map) {
    for (i32 y = 0; y < map->height; y++) {
        for (i32 x = 0; x < map->width; x++) {
            Color color = BLACK;

            color = map_get_tile_color(map->tiles[y][x]);

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
