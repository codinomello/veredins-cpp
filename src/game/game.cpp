#include <vector>

#include "game.h"
#include "core/camera.h"
#include "core/math.h"
#include "entity/player.h"
#include "entity/veredim.h"
#include "input/input.h"
#include "world/map.h"
#include "ui/ui.h"
#include "raylib.h"

static Player player;
static Veredim veredim;
static std::vector<Veredim> veredins;
static InputState input;
static TileMap map;

void game_init(Game* game) {
    map_init(&map);
    
    player_init(&player, WINDOW_WIDTH, WINDOW_HEIGHT);

    for (u32 i = 0; i < 15; ++i) {
        veredins.push_back(
            veredim_init(
                &veredim,
                player.pos.x + GetRandomValue(-300, 300),
                player.pos.y + GetRandomValue(-300, 300),
                ELEMENT_FIRE << (i % 6)
            )
        );
    }

    camera_init(&game->game_camera, player.pos.x, player.pos.y);

    game->rl_camera.target = {
        game->game_camera.x, game->game_camera.y
    };
    game->rl_camera.offset = {
        640.0f, 360.0f
    };
    game->rl_camera.rotation = 0.0f;
    game->rl_camera.zoom = 1.0f;
}

void game_update(Game* game, f32 dt) {
    input_update(&input);

    player_update(&player, dt, input.x, input.y);

    for (u32 i = 0; i < veredins.size(); ++i) {
        veredim_update(&veredins[i], dt, player.pos.x, player.pos.y, i);
    }

    f32 look_x = player.pos.x + input.x * 40.0f;
    f32 look_y = player.pos.y + input.y * 40.0f;

    camera_update(&game->game_camera, look_x, look_y, dt);
    camera_update(&game->game_camera, player.pos.x, player.pos.y, dt);

    game->rl_camera.target.x = game->game_camera.x;
    game->rl_camera.target.y = game->game_camera.y;
}

void game_render(Game* game) {
    map_draw(&map);
    player_draw(&player);

    for (auto& veredim : veredins) {
        veredim_draw(&veredim);
    }
}

void game_render_ui(Game* game) {
    ui_fps_draw();
    ui_elapsed_time_draw(game->time);
}

void game_shutdown(Game* game) {
    game->is_running = false;
}