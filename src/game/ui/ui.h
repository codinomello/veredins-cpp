#ifndef GAME_UI_UI_H
#define GAME_UI_UI_H

#include "../constants/constants.h"
#include "../core/types.h"
#include "raylib.h"

typedef struct Ui {
   // TODO: fazer algo aqui se precisar no futuro
} Ui;

void ui_fps_draw(const Font& font);
void ui_elapsed_time_draw(const Font& font, f32 time);

#endif // GAME_UI_UI_H