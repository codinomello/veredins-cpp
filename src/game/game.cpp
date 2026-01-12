#include <algorithm>

#include "logic/logic.h"
#include "raymath.h"
#include "game.h"

void game_init(Game* g) {
    // inicializa a janela antes de carregar recursos
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Veredins");
    SetTargetFPS(60);
    *g = {
        .ui = {
            .font = LoadFont(FONT_PATH.c_str())
        },
        .elapsed_time = 0,
        .is_running = true
    };

    // inicialização dos structs (mapa, player & ui)
    map_init(&g->map);
    player_init(&g->player, WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f);
    ui_init(&g->ui, LoadFont(FONT_PATH.c_str()));

    // inicialização dos veredins
    for (int i = 0; i < INITIAL_VEREDIM_COUNT; i++) {
        std::unique_ptr v = std::make_unique<Veredim>();
        veredim_init(v.get(), g->player.pos.x, g->player.pos.y, (1 << (i/3)));
        g->veredins.push_back(std::move(v));
    }

    // câmera raylib
    g->rl_camera = { 
        .offset = { WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f },
        .target = g->player.pos,
        .rotation = 0.0f,
        .zoom = 1.0f
    };
}

void game_update(Game* g, f32 dt) {
    // atualizações de sistema
    player_update(&g->player, &g->map, &g->input, dt);
    input_update(&g->input);
    ui_update(&g->ui, dt);

    // variáveis auxiliares
    Creature* target = g->creatures.empty() ? nullptr : g->creatures[0].get();
    u32 veredim_count = (u32)g->veredins.size();

    // lógica de arremesso
    if (g->input.throw_veredim) {
        for (u32 i = 0; i < veredim_count; i++) {
            Veredim* v = g->veredins[i].get();
            if (v->state == VEREDIM_FOLLOW) {
                Vector2 mouse_world = GetScreenToWorld2D(GetMousePosition(), g->rl_camera);
                v->state = VEREDIM_THROWN;
                v->vel = Vector2Scale(Vector2Normalize(Vector2Subtract(mouse_world, v->pos)), 400.0f);
                break; 
            }
        }
    }

    u32 total_veredins = (u32)g->veredins.size();
    // loop único de veredins: movimento, colisão e combate
    for (u32 i = 0; i < total_veredins; i++) {
        Veredim* v = g->veredins[i].get();
        
        veredim_update(v, &g->player, target, i, dt);
        logic_check_map_collision(&v->pos, v->radius, &g->map);

        if (g->input.whistle) {
            DrawCircleV(
                g->player.pos,
                100,
                Fade(YELLOW, 0.3f)
            );
            v->state = VEREDIM_FOLLOW;
            v->vel = { 1.0f, 1.0f};
        }

        // combate contra criaturas
        for (u32 j = 0; j < (u32)g->creatures.size(); j++) {
            Creature* c = g->creatures[j].get();
            if (CheckCollisionCircles(v->pos, v->radius, c->pos, c->radius)) {
                c->health -= 10;
                if (c->health <= 0) c->is_alive = false;
            }
        }
    }

    // atualização e limpeza de criaturas (loop decrescente)
    for (int i = (int)g->creatures.size() - 1; i >= 0; i--) {
        Creature* c = g->creatures[i].get();
        if (!c->is_alive) {
            // remove o elemento na posição i
            g->creatures.erase(g->creatures.begin() + i);
        } else {
            creature_update(c, dt, g->player.pos);
        }
    }

    // câmera e tempo
    Vector2 look_dir = Vector2Scale(g->input.move, 40.0f);
    Vector2 look_target = Vector2Add(g->player.pos, look_dir);
    g->rl_camera.target = Vector2Lerp(g->rl_camera.target, look_target, 6.0f * dt);
    
    g->elapsed_time += dt;
}

void game_render(Game* g) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(g->rl_camera);
    map_draw(&g->map);
    for (auto& v : g->veredins) veredim_draw(v.get());
    for (auto& c : g->creatures) creature_draw(c.get());
    player_draw(&g->player);
    EndMode2D();
    ui_draw(&g->ui);
    EndDrawing();
}


void game_shutdown(Game* g) {
    UnloadFont(g->ui.font);
    CloseWindow();
}