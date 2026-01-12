#include "camera.h"
#include "raymath.h"

void camera_init(GameCamera* cam, Vector2 pos) {
    // inicializa posição e alvo no mesmo ponto
    cam->pos = pos;
    cam->target = pos;
    cam->smooth = 8.0f;
}

void camera_update(GameCamera* cam, Vector2 target, f32 dt) {
    cam->target = target;
    
    // interpola a posição inteira de uma vez usando a função da raymath
    cam->pos = Vector2Lerp(cam->pos, cam->target, cam->smooth * dt);
}