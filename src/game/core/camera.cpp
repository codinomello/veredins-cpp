#include "game/core/camera.h"
#include "game/core/math.h"

void camera_init(GameCamera* cam, f32 x, f32 y) {
    cam->x = x;
    cam->y = y;
    cam->target_x = x;
    cam->target_y = y;
    cam->smooth = 8.0f;
}

void camera_update(GameCamera* cam, f32 target_x, f32 target_y, f32 dt) {
    cam->target_x = target_x;
    cam->target_y = target_y;

    cam->x = lerp(cam->x, cam->target_x, cam->smooth * dt);
    cam->y = lerp(cam->y, cam->target_y, cam->smooth * dt);
}
