#ifndef GAME_INPUT_INPUT_H
#define GAME_INPUT_INPUT_H

#include "game/core/types.h"

typedef struct InputState {
    f32 x;
    f32 y;
} InputState;

void input_update(InputState* input);

#endif // GAME_INPUT_INPUT_H