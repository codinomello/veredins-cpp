#ifndef GAME_LOGIC_PHYSICS_H
#define GAME_LOGIC_PHYSICS_H

#include "game/world/map.h"
#include "game/core/types.h"
#include "raylib.h"

void logic_check_map_collision(Vector2* pos, f32 radius, const Map* map);

#endif // GAME_LOGIC_PHYSICS_H