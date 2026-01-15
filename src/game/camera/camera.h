#ifndef VEREDINS_GAME_CAMERA_CAMERA_H
#define VEREDINS_GAME_CAMERA_CAMERA_H

#include "game/core/types.h"

#include "raylib.h"

typedef struct GameCamera {
    Camera2D rl;
    f32 smooth;
} GameCamera;

void camera_init(GameCamera* cam, Vector2 pos);
void camera_update(GameCamera* cam, Vector2 player_pos, Vector2 player_look, f32 dt);

#endif // VEREDINS_GAME_CAMERA_CAMERA_H