#include "input.h"

#include "raymath.h"

void input_init(Input* input) {
    *input = { 0 };
}

void input_update(Input* input, GameCamera* game_cam) {
    // Resetar direcional
    input->move = { 0, 0 };
    
    // Movimento
    if (IsKeyDown(KEY_A)) input->move.x -= 1.0f;
    if (IsKeyDown(KEY_D)) input->move.x += 1.0f;
    if (IsKeyDown(KEY_W)) input->move.y -= 1.0f;
    if (IsKeyDown(KEY_S)) input->move.y += 1.0f;
    
    // Normaliza para o player não andar mais rápido na diagonal
    if (Vector2Length(input->move) > 0) {
        input->move = Vector2Normalize(input->move);
    }
    
    // Ações
    input->whistle = IsKeyPressed(KEY_SPACE);
    input->throw_veredim = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    input->dismiss_veredim = IsKeyPressed(KEY_Q);
    input->switch_veredim_type = IsKeyPressed(KEY_TAB);
    
    // câmera 2D temporária
    Camera2D rl_cam = { 0 };
    rl_cam.target = game_cam->pos;
    rl_cam.offset = game_cam->offset;
    rl_cam.zoom = 1.0f;

    input->mouse_pos = GetScreenToWorld2D(GetMousePosition(), rl_cam);
}