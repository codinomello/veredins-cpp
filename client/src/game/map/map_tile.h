#ifndef VEREDINS_GAME_MAP_MAP_TILE_H
#define VEREDINS_GAME_MAP_MAP_TILE_H

#include "game/core/types.h"
#include "game/core/constants.h"

typedef enum Tile {
    TILE_EMPTY = 0,
    TILE_GRASS = 1,
    TILE_DIRT  = 2,
    TILE_WATER = 3,
    TILE_ROCK  = 4
} TileType;


bool tile_is_solid(Tile t);

#endif // VEREDINS_GAME_MAP_MAP_TILE_H