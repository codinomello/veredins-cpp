#include <memory>
#include <vector>
#include <string>
#include <cmath>

#include "game.h"
#include "constants/constants.h"
#include "core/camera.h"
#include "core/math.h"
#include "entities/player.h"
#include "entities/veredim.h"
#include "input/input.h"
#include "world/map.h"
#include "ui/ui.h"
#include "raylib.h"

static std::unique_ptr<Player> player;
static std::unique_ptr<TileMap> map;
static std::unique_ptr<Input> input;
static std::vector<std::unique_ptr<Veredim>> veredins;

void game_init(Game* game) {
    game->is_running = true;
    game->title = "Veredins";
    game->background_color = WHITE;
    game->font = LoadFontEx(FONT_PATH, UI_FONT_SIZE, NULL, 0);
    game->time = GetTime();

    map = std::make_unique<TileMap>();
    player = std::make_unique<Player>();
    input = std::make_unique<Input>();

    map_init(map.get());
    player_init(player.get(), (f32)WINDOW_WIDTH, (f32)WINDOW_HEIGHT, 30.0f, 30.0f);

    const int total_veredins = 18;
    for (u32 i = 0; i < total_veredins; ++i) {
        auto v = std::make_unique<Veredim>();
        
        *v = veredim_init(v.get(), player->pos.x, player->pos.y, (1 << (i / 3)));
        v->state = VEREDIM_FOLLOWING; 
        v->angle = (f32)i * 0.5f;
        veredins.push_back(std::move(v));
    }

    camera_init(&game->game_camera, player->pos.x, player->pos.y);
    game->rl_camera.target = { game->game_camera.x, game->game_camera.y };
    game->rl_camera.offset = { 640.0f, 360.0f };
    game->rl_camera.rotation = 0.0f;
    game->rl_camera.zoom = 1.0f;
}

void game_update(Game* game, f32 dt) {
    input_update(input.get());
    player_update(player.get(), dt, input->x, input->y);

    for (u32 i = 0; i < (u32)veredins.size(); ++i) {
        veredim_update(veredins[i].get(), dt, player->pos.x, player->pos.y, i);
    }

    f32 look_x = player->pos.x + input->x * 40.0f;
    f32 look_y = player->pos.y + input->y * 40.0f;

    camera_update(&game->game_camera, look_x, look_y, dt);
    game->rl_camera.target.x = game->game_camera.x;
    game->rl_camera.target.y = game->game_camera.y;

    game->time += dt;
}

void game_render(Game* game) {
    BeginMode2D(game->rl_camera);
    
    map_draw(map.get());
    
    for (const auto& v : veredins) {
        veredim_draw(v.get());
    }
    
    player_draw(player.get());
    
    EndMode2D();
    
    game_render_ui(game);
}

void game_render_ui(Game* game) {
    ui_fps_draw(game->font);
    ui_elapsed_time_draw(game->font, game->time);
}

void game_shutdown(Game* game) {
    UnloadFont(game->font);
    veredins.clear();
    player.reset();
    map.reset();
    input.reset();
    game->is_running = false;
}