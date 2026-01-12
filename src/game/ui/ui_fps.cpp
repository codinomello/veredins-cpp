#include "ui.h"

void ui_draw_fps(Ui* ui) {
    std::string text = TextFormat("FPS: %d", GetFPS());
    ui_draw_label(ui, text, 0, LIME);
}