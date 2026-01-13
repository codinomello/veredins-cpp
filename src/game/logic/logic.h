#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <memory>

#include "game/entities/entity.h"
#include "game/core/types.h"

#include "raylib.h"

// forward declaration para evitar inclusão circular
struct Game;

void logic_spawn_wave(Game* g);
void logic_spawn_creatures(Game* g, u32 count);
void logic_spawn_objects(Game* g, u32 count);

#endif