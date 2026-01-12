#ifndef GAME_UI_UI_H
#define GAME_UI_UI_H

#include "game/constants/constants.h"
#include "game/core/types.h"
#include "raylib.h"

typedef struct Ui {
    Color background_color;
    Font font;
    f32 time;
    bool show_debug;
} Ui;

void ui_init(Ui* ui, Font font);
void ui_update(Ui* ui, f32 dt);
void ui_draw(Ui* ui);
void ui_shutdown(Ui* ui);

// widgets
void ui_draw_fps(Ui* ui);
void ui_draw_time(Ui* ui);
void ui_draw_text(Ui* ui, const char* text, i32 x, i32 y, i32 size, Color color);
void ui_draw_debug(Ui* ui);

#endif // GAME_UI_UI_H