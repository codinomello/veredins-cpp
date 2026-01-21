#include <vector>
#include <memory>

#include "game/elements/element.h"
#include "game/entities/veredim.h"
#include "input.h"

#include "raymath.h"

void input_init(Input* input) {
    *input = { 0 };
}

void input_update(Input* input, GameCamera* cam, Ui* ui) {
    // resetar direcional
    input->move = { 0 };
    
    // movimento
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    input->move.y -= 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  input->move.x -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  input->move.y += 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) input->move.x += 1.0f;
    
    // normaliza para o player não andar mais rápido na diagonal
    if (Vector2Length(input->move) > 0) {
        input->move = Vector2Normalize(input->move);
    }
    
    // input de troca de elemento
    if (IsKeyPressed(KEY_TAB)) {
        ui->selected_element = (Element)(ui->selected_element << 1);
        if (ui->selected_element > ELEMENT_METAL) ui->selected_element = ELEMENT_FIRE;
    }

    // ações
    input->whistle = IsKeyDown(KEY_SPACE);
    input->throw_veredim = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    input->dismiss_veredim = IsKeyPressed(KEY_Q);
    input->switch_veredim_type = IsKeyPressed(KEY_TAB);
    input->mouse_pos = GetScreenToWorld2D(GetMousePosition(), cam->rl);
}