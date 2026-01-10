#include <string>

#include "../game.h"
#include "../ui/ui.h"
#include "raylib.h"

void ui_fps_draw(const Font& font) {
    int fps = GetFPS();
    const std::string text = TextFormat("FPS: %i", fps);

    Vector2 text_size = MeasureTextEx(font, text.c_str(), (f32)UI_FONT_SIZE, 1.0f);
    DrawTextEx(
        font,
        text.c_str(),
        (Vector2){ (f32)WINDOW_WIDTH - text_size.x - UI_MARGIN - 50, (f32)UI_MARGIN },
        (f32)UI_FONT_SIZE,
        1.0f,
        WHITE
    );
}

void ui_elapsed_time_draw(const Font& font, f32 time) {
    const std::string text = TextFormat("Time: %.2f s", time);
    
    f32 posY = (f32)WINDOW_HEIGHT - (f32)UI_FONT_SIZE - (f32)UI_MARGIN;

    DrawTextEx(
        font,
        text.c_str(),
        (Vector2){ (f32)UI_MARGIN, posY },
        (f32)UI_FONT_SIZE,
        1.0f,
        WHITE
    );
}