#include "game/ui/ui.h"
#include "raylib.h"

void ui_draw() {
    int fps = GetFPS();
    DrawText(
        TextFormat("FPS: %i", fps),
        10,
        10,
        20,
        WHITE
    );
}