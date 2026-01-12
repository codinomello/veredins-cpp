#include "ui.h"

void ui_init(Ui* ui, Font font) {
    ui->background_color = WHITE;
    ui->font = font;
    ui->time = 0.0f;
    ui->show_debug = true;
}

void ui_update(Ui* ui, f32 dt) {
    ui->time += dt;
}

void ui_draw(Ui* ui) {
    ui_draw_fps(ui);
    ui_draw_time(ui);

    if (ui->show_debug) {
        ui_draw_debug(ui);
    }
}

void ui_shutdown(Ui* ui) {
    // por enquanto nada
}