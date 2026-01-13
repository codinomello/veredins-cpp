#ifndef GAME_CORE_CAMERA_H
#define GAME_CORE_CAMERA_H

#include "types.h"

#include "raylib.h"

typedef struct GameCamera {
    Vector2 pos;    // posição atual (interpolada)
    Vector2 target; // posição do objetivo (player)
    Vector2 offset; // centro da tela (WINDOW_WIDTH/2, WINDOW_HEIGHT/2)
    f32 smooth;     // velocidade de suavização
} GameCamera;

void camera_init(GameCamera* game_cam, Vector2 position);
void camera_update(GameCamera* game_cam, Vector2 target, f32 dt);

#endif // GAME_CORE_CAMERA_H