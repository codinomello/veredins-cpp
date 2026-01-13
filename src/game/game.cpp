#include "game/core/constants.h"
#include "logic/logic.h"
#include "game.h"

#include "raymath.h"

void game_init(Game* g) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Veredins");
    SetTargetFPS(60);

    g->time = 0;
    g->wave = 1;
    g->is_running = true;
    g->is_game_over = false;
    g->window_icon = LoadImage(WINDOW_ICON_PATH); 
    if (g->window_icon.data != nullptr) {
        SetWindowIcon(g->window_icon);
        UnloadImage(g->window_icon); 
    }
    g->ui.font = LoadFontEx(FONT_PATH, UI_FONT_SIZE, nullptr, 0);
    g->background_color = GetColor(0x181818FF);
    // configura o filtro da fonte para não ficar borrada ao redimensionar
    SetTextureFilter(g->ui.font.texture, TEXTURE_FILTER_BILINEAR);

    // inicializa mundo e player
    map_init(&g->map);
    player_init(&g->player, { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });
    camera_init(&g->camera, g->player.pos);

    // inicializa ui
    ui_init(&g->ui, GetFontDefault());

    // inicializa veredins iniciais
    for (u32 i = 0; i < INITIAL_VEREDIM_COUNT; i++) {
        auto v = std::make_unique<Veredim>();
        veredim_init(v.get(), g->player.pos.x, g->player.pos.y, ELEMENT_FIRE);
        g->veredins.push_back(std::move(v));
    }

    logic_spawn_wave(g);
}

void game_update(Game* g, f32 dt) {
    if (g->is_game_over) {
        if (IsKeyPressed(KEY_R)) game_init(g);
        return;
    }
    g->time += dt;

    // atualiza o player
    player_update(&g->player, &g->map, &g->input, dt);

    // atualiza o input
    input_update(&g->input, &g->camera, &g->ui);

    // atualiza a camera
    camera_update(&g->camera, g->player.pos, g->input.move, dt);

    // atualiza os veredins (sistema de órbita e seguimento)
    for (auto i = 0; i < g->veredins.size(); i++) {
        veredim_update(g->veredins[i].get(), &g->player, (u32)g->veredins.size(), (u32)i, dt);
    }

    // TEMPORARIO
    if (g->input.throw_veredim) {
        for (u32 i = 0; i < (u32)g->veredins.size(); i++) {
            Veredim* v = (g->veredins)[i].get();
            
            // só arremessa se ele estiver a seguir o player (disponível na órbita)
            if (v->state == VEREDIM_FOLLOW) {
                v->state = VEREDIM_THROWN;
                v->state_timer = 0.0f;
                
                Vector2 diff = Vector2Subtract(g->input.mouse_pos, v->pos);
                v->vel = Vector2Scale(Vector2Normalize(diff), 500.0f);
                
                break; 
            }
        }
    }
  
    // atualiza as criaturas
    for (auto& c : g->creatures) {
        if (c->is_alive) {
            creature_update(c.get(), dt, g->player.pos);
        }
    }

    // remove as criaturas
    for (int i = g->creatures.size() - 1; i >= 0; i--) {
        Creature* c = g->creatures[i].get();
        if (!c->is_alive) {
            // remove o elemento na posição i
            g->creatures.erase(g->creatures.begin() + i);
        } else {
            creature_update(c, dt, g->player.pos);
        }
    }

    // sincroniza a ui
    g->ui.score = g->wave * 100;
    g->ui.veredim_count = (i32)g->veredins.size();
    if (g->player.health <= 0) g->is_game_over = true;
}

void game_render(Game* g) {
    BeginDrawing();
    ClearBackground(g->background_color);
    
    BeginMode2D(g->camera.rl);

        // mundo
        map_draw(&g->map);

        // entidades vetorizadas
        for (auto& o : g->objects)   object_draw(o.get());
        for (auto& c : g->creatures) creature_draw(c.get());
        for (auto& v : g->veredins)  veredim_draw(v.get(), g->time);
        
        // jogador
        player_draw(&g->player);

    EndMode2D();

    // interface
    ui_draw(&g->ui, g->player.health, g->player.max_health, g->wave, g->time, g->is_game_over);

    EndDrawing();
}

void game_shutdown(Game* g) {
    UnloadFont(g->ui.font);
    UnloadImage(g->window_icon);
    map_shutdown(&g->map);
    CloseWindow();
}