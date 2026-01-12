#ifndef GAME_WORLD_MAP_H
#define GAME_WORLD_MAP_H

#include "../constants/constants.h"
#include "../core/types.h"
#include "tile.h"
#include "raylib.h"

typedef struct Map {
    u32 width;
    u32 height;
    TileType type;
    TileType tiles[MAP_HEIGHT][MAP_WIDTH];
} Map;

void map_init(Map* m);
Color map_get_tile_color(Tile t);
void map_draw(const Map* m);

#endif // GAME_WORLD_MAP_H