#include "../game.h"
#include "../ui/ui.h"

#include "raylib.h"

void ui_fps_draw() {
    int fps = GetFPS();
    DrawText(
        TextFormat("FPS: %i", fps),
        WINDOW_WIDTH - 10,
        WINDOW_HEIGHT - 10,
        WINDOW_HEIGHT - 10,
        WHITE
    );
}

void ui_elapsed_time_draw(f32 time) {
    DrawText(
        TextFormat("Time: %.2f s", time),
        8,
        WINDOW_HEIGHT - 10,
        WINDOW_HEIGHT - 10,
        WHITE
    );
}