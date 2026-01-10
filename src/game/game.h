#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <string>

#include "core/types.h"
#include "core/camera.h"
#include "raylib.h"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

typedef struct Game {
    bool is_running;
    std::string title;
    Color background_color;
    f32  time;
    GameCamera game_camera;
    Camera2D rl_camera;
} Game;

void game_init(Game* game);
void game_update(Game* game, f32 dt);
void game_render(Game* game);
void game_render_ui(Game* game);
void game_shutdown(Game* game);

#endif // GAME_GAME_H