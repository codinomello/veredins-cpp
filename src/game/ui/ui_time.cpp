#include "ui.h"

void ui_draw_time(Ui* ui) {
    std::string text = TextFormat("Time: %.2f s", ui->time);
    ui_draw_label(ui, text, 22.0f, WHITE);
}