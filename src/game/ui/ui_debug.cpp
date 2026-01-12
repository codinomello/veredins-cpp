#include "ui.h"

void ui_draw_debug(Ui* ui) {
    DrawTextEx(
        ui->font,
        "DEBUG MODE",
        (Vector2){ UI_MARGIN, UI_MARGIN + 44 },
        UI_FONT_SIZE,
        1.0f,
        YELLOW
    );
}