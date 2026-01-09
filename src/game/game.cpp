#include "game/game.h"
#include "game/entity/player.h"
#include "game/entity/veredim.h"
#include "game/input/input.h"

static Player player;
static Veredim veredim;
static InputState input;

void game_init(Game* game) {
    (void)game;

    player_init(&player, 640.0f, 360.0f);
    veredim_init(&veredim, 700.0f, 360.0f, ELEMENT_PLANT);
}

void game_update(Game* game, f32 dt) {
    (void)game;

    input_update(&input);
    player_update(&player, dt, input.x, input.y);
}

void game_render(Game* game) {
    (void)game;

    player_draw(&player);
    veredim_draw(&veredim);
}

void game_shutdown(Game* game) {
    game->is_running = false;
}