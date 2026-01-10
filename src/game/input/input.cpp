#include "../input/input.h"
#include "raylib.h"

void input_update(InputState* input) {
    input->x = 0.0f;
    input->y = 0.0f;

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        input->x -= 1.0f;  
    }

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        input->x += 1.0f;
    }

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        input->y -= 1.0f;  
    }
    
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        input->y += 1.0f;
    }
}
