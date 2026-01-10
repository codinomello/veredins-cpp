#ifndef GAME_WORLD_MAP_H
#define GAME_WORLD_MAP_H

#include "../core/types.h"
#include "tile.h"
#include "raylib.h"

constexpr int MAP_WIDTH = 64;
constexpr int MAP_HEIGHT = 64;

typedef struct {
    i32 width;
    i32 height;
    TileType tiles[MAP_HEIGHT][MAP_WIDTH];
} TileMap;

void map_init(TileMap* map);
Color map_get_tile_color(u32 tile_type);
void map_draw(const TileMap* map);

#endif // GAME_WORLD_MAP_H