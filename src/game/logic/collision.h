#ifndef GAME_LOGIC_COLLISION_H
#define GAME_LOGIC_COLLISION_H

#include "../core/types.h"
#include "raylib.h"

bool aabb_intersect(f32 ax, f32 ay, f32 aw, f32 ah, f32 bx, f32 by, f32 bw, f32 bh);
bool circles_overlap(Vector2 a, f32 ra, Vector2 b, f32 rb);

#endif // GAME_LOGIC_COLLISION_H