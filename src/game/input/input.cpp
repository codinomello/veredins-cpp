#include "input.h"
#include "raylib.h"

void input_init(Input* input) {
    input->move = { 0.0f, 0.0f };
    input->whistle = false;
    input->throw_veredim = false;
    input->attack = false;
}

void input_update(Input* input) {
    // reset por frame
    input->move = { 0.0f, 0.0f };
    input->whistle = false;
    input->throw_veredim = false;
    input->attack = false;

    // movimento
    if (IsKeyDown(KEY_A)) input->move.x -= 1.0f;
    if (IsKeyDown(KEY_D)) input->move.x += 1.0f;
    if (IsKeyDown(KEY_W)) input->move.y -= 1.0f;
    if (IsKeyDown(KEY_S)) input->move.y += 1.0f;

    // ações
    if (IsKeyPressed(KEY_SPACE)) {
        input->whistle = true;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        input->throw_veredim = true;
    }

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        input->attack = true;
    }
}