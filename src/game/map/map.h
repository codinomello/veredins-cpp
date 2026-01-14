#ifndef GAME_MAP_MAP_H
#define GAME_MAP_MAP_H

#include "game/core/types.h"

#include "raylib.h"

typedef struct Map {
    i32 width;
    i32 height;
    u8* tiles;
} Map;

void map_init(Map* map);
void map_draw(const Map* map);
bool map_is_solid(const Map* map, i32 tile_x, i32 tile_y);
void map_shutdown(Map* map);

#endif // GAME_MAP_MAP_H