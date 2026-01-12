#include "game/core/camera.h"
#include "game/core/math.h"

void camera_init(GameCamera* game_cam, Vector2 position) {
    game_cam->position = position;
    game_cam->target = position;
    game_cam->smooth = 8.0f;
}


void camera_update(GameCamera* game_cam, Vector2 target, f32 dt) {
    game_cam->target = target;

    game_cam->position = {
        lerp(game_cam->position.x, game_cam->target.x, game_cam->smooth * dt),
        lerp(game_cam->position.y, game_cam->target.y, game_cam->smooth * dt)
    };
}
