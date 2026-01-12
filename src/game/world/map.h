#ifndef GAME_WORLD_MAP_H
#define GAME_WORLD_MAP_H

#include "game/core/constants.h"
#include "game/core/types.h"
#include "tile.h"
#include "raylib.h"

typedef struct Map {
    u32 width;
    u32 height;
    TileType type;
    TileType tiles[MAP_HEIGHT][MAP_WIDTH];
} Map;

void map_init(Map* m);
bool map_is_solid(const Map* m, int x, int y);
Color map_get_tile_color(Tile t);
void map_draw(const Map* m);

#endif // GAME_WORLD_MAP_H