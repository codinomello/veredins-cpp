#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "core/types.h"

struct Game {
    bool running;
    f32  time;
};

void game_init(Game* game);
void game_update(Game* game, f32 dt);
void game_render(Game* game);
void game_shutdown(Game* game);

#endif // GAME_GAME_H