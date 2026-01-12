#ifndef GAME_CORE_CAMERA_H
#define GAME_CORE_CAMERA_H

#include "types.h"
#include "raylib.h"

typedef struct GameCamera {
    Vector2 pos;
    Vector2 target;
    f32 smooth;
} GameCamera;

void camera_init(GameCamera* cam, Vector2 position);
void camera_update(GameCamera* cam, Vector2 target, f32 dt);

#endif // GAME_CORE_CAMERA_H