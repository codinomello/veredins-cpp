#ifndef GAME_INPUT_INPUT_H
#define GAME_INPUT_INPUT_H

#include "game/core/types.h"
#include "game/core/camera.h"

#include "raylib.h"

typedef struct Input {
    Vector2 move;             // w, a, s, d - move o player
    Vector2 mouse_pos;        // posição do mouse no mundo
    bool whistle;             // space - chama todos veredims
    bool throw_veredim;       // botão esquerdo do mouse - arremessa veredim
    bool dismiss_veredim;     // d - dispensa veredim selecionado
    bool switch_veredim_type; // tab - troca tipo de veredim a arremessar
} Input;

void input_init(Input* input);
void input_update(Input* input, GameCamera* game_cam);

#endif // GAME_INPUT_INPUT_H