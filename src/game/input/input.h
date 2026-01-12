#ifndef GAME_INPUT_INPUT_H
#define GAME_INPUT_INPUT_H

#include "game/core/types.h"
#include "raylib.h"

typedef struct Input {
    Vector2 move;
    bool whistle;       // chamar veredins
    bool throw_veredim; // arremessar
    bool attack;        // futuro
} Input;

void input_init(Input* input);
void input_update(Input* input); // lê o teclado e mouse

#endif // GAME_INPUT_INPUT_H