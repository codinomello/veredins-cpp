#include "tile.h"

bool tile_is_solid(TileType t) {
    return (t == TILE_ROCK || t == TILE_WATER);
}