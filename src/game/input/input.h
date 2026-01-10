#ifndef GAME_INPUT_INPUT_H
#define GAME_INPUT_INPUT_H

#include "../core/types.h"

typedef struct Input {
    f32 x;
    f32 y;
} Input;

void input_update(Input* input);

#endif // GAME_INPUT_INPUT_H