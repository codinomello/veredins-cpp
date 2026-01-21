#ifndef VEREDINS_GAME_UI_UI_H
#define VEREDINS_GAME_UI_UI_H

#include "common/types.h"
#include "game/elements/element.h"

#include "raylib.h"

typedef struct Ui {
    Font font;
    i32 score;
    i32 veredim_count;
    u16 selected_element;
} Ui;

void ui_init(Ui* Ui);
void ui_update(Ui* Ui, f32 dt);
void ui_draw(const Ui* ui, i32 player_health, i32 player_max_health, i32 wave, f32 game_time, bool game_over);

#endif // VEREDINS_GAME_UI_UI_H