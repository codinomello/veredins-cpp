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

void ui_draw_label(Ui* ui, std::string text, f32 y_offset, Color color) {
    DrawTextEx(
        ui->font,
        text.c_str(),
        { (f32)UI_MARGIN, (f32)UI_MARGIN + y_offset },
        (f32)UI_FONT_SIZE,
        1.0f,
        color
    );
}

void ui_draw_text(Ui* ui, std::string text, i32 x, i32 y, i32 size, Color color) {
    DrawTextEx(
        ui->font,
        text.c_str(),
        { (f32)x, (f32)y },
        (f32)size,
        1.0f,
        color
    );
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