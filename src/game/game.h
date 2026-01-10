#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <string>

#include "constants/constants.h"
#include "core/types.h"
#include "core/camera.h"
#include "ui/ui.h"
#include "raylib.h"

typedef struct Game {
    std::string title;
    f64  time;
    Color background_color;
    GameCamera game_camera;
    Camera2D rl_camera;
    Font font;
    bool is_running;
} Game;

void game_init(Game* game);
void game_update(Game* game, f32 dt);
void game_render(Game* game);
void game_render_ui(Game* game);
void game_shutdown(Game* game);

#endif // GAME_GAME_H