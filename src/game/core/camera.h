#ifndef GAME_CORE_CAMERA_H
#define GAME_CORE_CAMERA_H

#include "types.h"

typedef struct GameCamera {
    f32 x;
    f32 y;

    f32 target_x;
    f32 target_y;

    f32 smooth;
} GameCamera;

void camera_init(GameCamera* cam, f32 x, f32 y);
void camera_update(GameCamera* cam, f32 target_x, f32 target_y, f32 dt);

#endif // GAME_CORE_CAMERA_H