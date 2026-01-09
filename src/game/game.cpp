#include "game.h"

void game_init(Game* game) {
    game->running = true;
    game->time = 0.0f;
}

void game_update(Game* game, f32 dt) {
    game->time += dt;
    // Update game logic here
}

void game_render(Game* game) {
    // Render game elements here
}

void game_shutdown(Game* game) {
    game->running = false;
    // Clean up resources here
}
