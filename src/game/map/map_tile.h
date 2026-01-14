#ifndef GAME_TILE_MAP_TILE_H
#define GAME_TILE_MAP_TILE_H

#include "game/core/types.h"

constexpr int TILE_SIZE = 32;

typedef enum Tile {
    TILE_EMPTY = 0,
    TILE_GRASS = 1,
    TILE_DIRT  = 2,
    TILE_WATER = 3,
    TILE_ROCK  = 4
} TileType;


bool tile_is_solid(Tile t);

#endif // GAME_TILE_MAP_TILE_H