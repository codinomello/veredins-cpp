#include "game/core/constants.h"
#include "camera.h"

#include "raymath.h"

void camera_init(GameCamera* game_cam, Vector2 pos) {
    *game_cam = {
        .pos = pos,
        .target = pos,
        .offset = Vector2{ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f },
        .smooth = 8.0f
    };
}

void camera_update(GameCamera* game_cam, Vector2 target, f32 dt) {
    // interpolação suave (lerp) para evitar movimentos bruscos
    game_cam->pos = Vector2Lerp(game_cam->pos, game_cam->target, game_cam->smooth * dt);
    game_cam->target = target;
}