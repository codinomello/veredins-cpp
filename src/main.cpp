#include "game/game.h"

Game game;

int main(void) {
    game_init(&game);

    while (!WindowShouldClose() && game.is_running) {
        f32 dt = GetFrameTime();
        game_update(&game, dt);
        game_render(&game);
    }
    
    game_shutdown(&game);

    return 0;
}