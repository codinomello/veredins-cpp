#include "ui.h"

void ui_draw_fps(Ui* ui) {
    char buffer[32];
    int fps = GetFPS();

    TextFormat(buffer, "FPS: %d", fps);

    DrawTextEx(
        ui->font,
        buffer,
        (Vector2){ UI_MARGIN, UI_MARGIN },
        UI_FONT_SIZE,
        1.0f,
        WHITE
    );
}