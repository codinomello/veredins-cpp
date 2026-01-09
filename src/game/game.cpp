#include <vector>

#include "game/game.h"
#include "game/core/math.h"
#include "game/entity/player.h"
#include "game/entity/veredim.h"
#include "game/input/input.h"
#include "game/ui/ui.h"
#include "raylib.h"

static Player player;
static Veredim veredim;
static std::vector<Veredim> veredins;
static InputState input;

void game_init(Game* game) {
    player_init(&player, 640.0f, 360.0f);

    for (u32 i = 0; i < 500; ++i) {
        veredins.push_back(
            veredim_init(
                &veredim,
                player.pos.x + GetRandomValue(-300, 300),
                player.pos.y + GetRandomValue(-300, 300),
                ELEMENT_FIRE << (i % 6)
            )
        );
    }
}

void game_update(Game* game, f32 dt) {
    input_update(&input);

    player_update(&player, dt, input.x, input.y);

    for (u32 i = 0; i < veredins.size(); ++i) {
        veredim_update(&veredins[i], dt, player.pos.x, player.pos.y, i);
    }
}

void game_render(Game* game) {
    player_draw(&player);

    for (auto& veredim : veredins) {
        veredim_draw(&veredim);
    }

    ui_draw();
}

void game_shutdown(Game* game) {
    game->is_running = false;
}