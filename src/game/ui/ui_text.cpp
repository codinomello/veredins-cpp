#include "ui.h"

void ui_draw_time(Ui* ui) {
    char buffer[64];
    TextFormat(buffer, "Time: %.2f s", ui->time);

    DrawTextEx(
        ui->font,
        buffer,
        (Vector2){ UI_MARGIN, UI_MARGIN + 22 },
        UI_FONT_SIZE,
        1.0f,
        WHITE
    );
}

void ui_draw_text(Ui* ui, const char* text, i32 x, i32 y, i32 size, Color color) {
    DrawTextEx(
        ui->font,
        text,
        (Vector2){ (f32)x, (f32)y },
        (f32)size,
        1.0f,
        color
    );
}