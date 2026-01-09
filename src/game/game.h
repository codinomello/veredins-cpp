#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <string>

#include "core/types.h"
#include "raylib.h"

typedef struct Game {
    bool is_running;
    std::string title;
    Color background_color;
    f32  time;
} Game;

void game_init(Game* game);
void game_update(Game* game, f32 dt);
void game_render(Game* game);
void game_shutdown(Game* game);

#endif // GAME_GAME_H