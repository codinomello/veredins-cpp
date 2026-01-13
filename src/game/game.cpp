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

    // inicializa mundo e player
    map_init(&g->map);
    player_init(&g->player, WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    camera_init(&g->game_camera, g->player.pos);
    
    // inicializa ui
    ui_init(&g->ui, GetFontDefault());

    // inicializa veredins iniciais
    for (u32 i = 0; i < INITIAL_VEREDIM_COUNT; i++) {
        auto v = std::make_unique<Veredim>();
        veredim_init(v.get(), g->player.pos.x, g->player.pos.y, ELEMENT_FIRE);
        g->veredins.push_back(std::move(v));
    }

    game_spawn_wave(g);
}

void game_spawn_wave(Game* g) {
    // spawna criaturas baseado na wave atual
    for (int i = 0; i < g->wave * 2; i++) {
        auto c = std::make_unique<Creature>();
        f32 rx = (f32)GetRandomValue(100, 1100);
        f32 ry = (f32)GetRandomValue(100, 600);
        creature_init(c.get(), rx, ry, ELEMENT_PLANT, (u8)g->wave);
        g->creatures.push_back(std::move(c));
    }
}

void game_update(Game* g, f32 dt) {
    if (g->is_game_over) {
        if (IsKeyPressed(KEY_R)) game_init(g);
        return;
    }

    g->time += dt;

    // input de troca de elemento
    if (IsKeyPressed(KEY_TAB)) {
        g->ui.selected_element = (EntityType)(g->ui.selected_element << 1);
        if (g->ui.selected_element > ELEMENT_LIGHT) g->ui.selected_element = ELEMENT_FIRE;
    }

    // update player e colisão
    player_update(&g->player, &g->map, &g->input, dt);
    input_update(&g->input, &g->game_camera);
    logic_check_map_collision(&g->player.pos, g->player.radius, &g->map);

    // update camera
    camera_update(&g->game_camera, g->player.pos, dt);

    // update veredins (sistema de órbita e seguimento)
    for (auto i = 0; i < g->veredins.size(); i++) {
        veredim_update(g->veredins[i].get(), &g->player, (u32)g->veredins.size(), (u32)i, dt);
        logic_check_map_collision(&g->veredins[i]->pos, g->veredins[i]->radius, &g->map);
    }

    // update criaturas
    for (auto& c : g->creatures) {
        if (c->is_alive) {
            creature_update(c.get(), dt, g->player.pos);
            logic_check_map_collision(&c->pos, c->radius, &g->map);
        }
    }

    // sincroniza ui
    g->ui.score = g->wave * 100;
    g->ui.veredim_count = (i32)g->veredins.size();
    if (g->player.health <= 0) g->is_game_over = true;
}

void game_render(Game* g) {
    BeginDrawing();
    ClearBackground(GetColor(0x181818FF));
    g->raylib_camera = {
        .offset = g->game_camera.offset, // o centro da tela que definimos no init
        .target = g->game_camera.pos,    // a posição interpolada (suave)
        .rotation = 0.0f,
        .zoom = 1.0f
    };
    BeginMode2D(g->raylib_camera);
        
        // mundo
        map_draw(&g->map);
        
        // entidades
        for (auto& o : g->objects)   object_draw(o.get());
        for (auto& c : g->creatures) creature_draw(c.get());
        for (auto& v : g->veredins)  veredim_draw(v.get(), g->time);
        
        player_draw(&g->player);

    EndMode2D();

    // interface
    ui_draw(&g->ui, g->player.health, g->player.max_health, g->wave, g->time, g->is_game_over);

    EndDrawing();
}

void game_shutdown(Game* g) {
    map_shutdown(&g->map);
    CloseWindow();
}