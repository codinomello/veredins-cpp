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
#include "entities/creature.h"
#include "input/input.h"
#include "logic/collision.h"
#include "world/map.h"
#include "ui/ui.h"
#include "raylib.h"
#include <algorithm>

static std::unique_ptr<Player> player;
static std::unique_ptr<TileMap> map;
static std::unique_ptr<Input> input;
static std::vector<std::unique_ptr<Veredim>> veredins;
static std::vector<std::unique_ptr<Creature>> creatures;

void game_init(Game* game) {
    // inicialização do jogo
    *game = (Game) {
        .title = "Veredins",
        .time = GetTime(),
        .background_color = WHITE,
        .font = LoadFontEx(FONT_PATH, UI_FONT_SIZE, NULL, 0),
        .is_running = true
    };

    // inicialização dos subsistemas
    map = std::make_unique<TileMap>();
    map_init(map.get());

    player = std::make_unique<Player>();
    player_init(player.get(), (f32)WINDOW_WIDTH, (f32)WINDOW_HEIGHT, 30.0f, 30.0f);

    input = std::make_unique<Input>();

    // veredins de teste
    const u32 total_veredins = 18;
    for (u32 i = 0; i < total_veredins; ++i) {
        auto v = std::make_unique<Veredim>();

        veredim_init(
            v.get(),
            player->position.x,
            player->position.y,
            (1u << (i / 3))
        );

        v->state = VEREDIM_FOLLOW;
        v->angle = (f32)i * 0.5f;

        veredins.push_back(std::move(v));
    }

    // inimigo de teste
    auto c = std::make_unique<Creature>();
    creature_init(c.get(), player->position.x + 200.0f, player->position.y);
    creatures.push_back(std::move(c));

    // câmera
    camera_init(&game->game_camera, player->position.x, player->position.y);
    game->rl_camera.target = { game->game_camera.x, game->game_camera.y };
    game->rl_camera.offset = { 640.0f, 360.0f };
    game->rl_camera.rotation = 0.0f;
    game->rl_camera.zoom = 1.0f;
}


void game_update(Game* game, f32 dt) {
    // input
    input_update(input.get());

    // player
    player_update(player.get(), map.get(), *input, dt);

    // veredins (follow / attack)
    for (u32 i = 0; i < veredins.size(); ++i) {
        veredim_update(
            veredins[i].get(),
            player.get(),
            nullptr,
            i,
            dt
        );
    }

    // creatures (ai / movimento)
    for (auto& c: creatures) {
        creature_update(c.get(), dt, player->position);
    }

    // combate: veredim x creature
    for (auto& v : veredins) {
        for (auto& c : creatures) {
            if (c->state == CREATURE_DEAD) {
                continue;
            }

            if (circles_overlap(
                v->position, v->radius,
                c->position, c->radius
            )) {
                if (v->state == VEREDIM_FOLLOW && v->attack_timer <= 0.0f) {
                    v->state = VEREDIM_ATTACK;
                    v->attack_timer = v->attack_cooldown;

                    i32 damage = v->attack;

                    if (veredim_element_is_strong(
                        v->element_mask,
                        c->element_mask
                    )) {
                        damage *= 2;
                    }

                    c->health -= damage;

                    if (c->health <= 0) {
                        c->state = CREATURE_DEAD;
                    }
                }
            }
        }
    }

    // combate: creature x player
    for (auto& c : creatures) {
        if (c->state == CREATURE_DEAD) {
            continue;
        }

        if (circles_overlap(
            c->position, c->radius,
            player->position, player->radius
        )) {
            if (c->attack_timer <= 0.0f) {
                player->health -= c->attack;
                c->attack_timer = c->attack_cooldown;
            }
        }
    }

    // remove creatures mortas
    creatures.erase(
        std::remove_if(
            creatures.begin(),
            creatures.end(),
            [](const std::unique_ptr<Creature>& c) {
                return c->state == CREATURE_DEAD;
            }
        ),
        creatures.end()
    );

    // camera (look ahead)
    player->look.x = player->position.x + input->x * 40.0f;
    player->look.y = player->position.y + input->y * 40.0f;

    camera_update(
        &game->game_camera,
        player->look.x,
        player->look.y,
        dt
    );

    // sincroniza câmera raylib
    game->rl_camera.target.x = game->game_camera.x;
    game->rl_camera.target.y = game->game_camera.y;

    // tempo
    game->time += dt;
}

void game_render(Game* game) {
    // mundo
    BeginMode2D(game->rl_camera);

    map_draw(map.get());

    // entidades
    for (auto& v : veredins) {
        veredim_draw(v.get());
    }

    for (auto& e : creatures) {
        creature_draw(e.get());
    }

    player_draw(player.get());

    // fim mundo
    EndMode2D();

    // render da interface gráfica estática
    game_render_ui(game);
}

void game_render_ui(Game* game) {
    // contador de fps
    ui_fps_draw(game->font);
    // tempo decorrido
    ui_elapsed_time_draw(game->font, game->time);
}

void game_shutdown(Game* game) {
    // descarrega recursos
    UnloadFont(game->font);

    veredins.clear();
    creatures.clear();
    player.reset();
    map.reset();
    input.reset();

    game->is_running = false;
}