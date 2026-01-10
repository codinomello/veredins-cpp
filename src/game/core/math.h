#ifndef GAME_CORE_MATH_H
#define GAME_CORE_MATH_H

#include "types.h"
#include "raylib.h"

f32 distance(f32 x1, f32 y1, f32 x2, f32 y2);
f32 lerp(f32 a, f32 b, f32 t);
Vector2 vector2_add(Vector2 v1, Vector2 v2);
Vector2 vector2_lerp(Vector2 v1, Vector2 v2, float amount);

#endif