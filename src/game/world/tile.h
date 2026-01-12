#ifndef GAME_WORLD_TILE_H
#define GAME_WORLD_TILE_H

#include "../core/types.h"

constexpr int TILE_SIZE = 32;

typedef enum TileType {
    TILE_EMPTY = 0,
    TILE_GRASS = 1,
    TILE_DIRT  = 2,
    TILE_WATER = 3,
    TILE_ROCK  = 4
} TileType;

typedef TileType Tile;

bool tile_is_solid(TileType t);

#endif // GAME_WORLD_TILE_H