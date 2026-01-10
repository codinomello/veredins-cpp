#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <string>

#include "constants/constants.h"
#include "core/types.h"
#include "core/camera.h"
#include "ui/ui.h"
#include "raylib.h"

typedef struct Game {
    bool is_running;
    std::string title;
    Color background_color;
    f64  time;
    GameCamera game_camera;
    Camera2D rl_camera;
    Font font;

    Game() : is_running(false), title(""), background_color(WHITE), time(0.0), game_camera{}, rl_camera{}, font{} {}
} Game;

void game_init(Game* game);
void game_update(Game* game, f32 dt);
void game_render(Game* game);
void game_render_ui(Game* game);
void game_shutdown(Game* game);

#endif // GAME_GAME_H