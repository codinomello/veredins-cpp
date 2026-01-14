#include <algorithm>

#include "core/constants.h"
#include "logic/logic.h"
#include "game.h"

#include "raymath.h"

void game_init(Game* g) {
    g->window_width = WINDOW_WIDTH;
    g->window_height = WINDOW_HEIGHT;
    g->window_title = "Veredins";
    
    // inicializa a janela com o nome de "Veredins"
    InitWindow(g->window_width, g->window_height, g->window_title.c_str());
    SetTargetFPS(60); // 60 fps para o PC não chorar

    // ícone de janela
    g->window_icon = LoadImage(WINDOW_ICON_PATH); 
    if (g->window_icon.data != nullptr) {
        SetWindowIcon(g->window_icon);
        UnloadImage(g->window_icon); 
    }
    
    // inicializa o mundo
    map_init(&g->map);
    
    // inicializa o jogador
    player_init(&g->player, { WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });

    // inicializa a câmera
    camera_init(&g->camera, g->player.pos);

    // inicializa o input
    input_init(&g->input);

    // inicializa ui
    ui_init(&g->ui);

    Element elements[] = {
        ELEMENT_FIRE, ELEMENT_WATER, ELEMENT_PLANT, ELEMENT_ELECTRIC, 
        ELEMENT_EARTH, ELEMENT_ICE, ELEMENT_POISON, ELEMENT_METAL
    };

    int total_spawned = 0;
    for (int e = 0; e < 8; e++) {
        for (int i = 0; i < 3; i++) {
            auto v = std::make_unique<Veredim>();
            veredim_init(v.get(), g->player.pos, elements[e]);

            // Organização por camadas:
            // Layer 0: primeiros 8 veredins (Raio menor)
            // Layer 1: veredins de 9 a 24 (Raio maior)
            if (total_spawned < 8) {
                v->layer = 0;
                v->orbit_angle = total_spawned * (360.0f / 8.0f);
            } else {
                v->layer = 1;
                v->orbit_angle = (total_spawned - 8) * (360.0f / 16.0f);
            }

            g->veredins.push_back(std::move(v));
            total_spawned++;
        }
    }

    g->time = 0;
    g->wave = 1;
    g->wave_timer = 0;
    g->is_running = true;
    g->is_game_over = false;
}

// void game_update(Game* g, f32 dt) {
//     if (g->is_game_over) {
//         if (IsKeyPressed(KEY_R)) game_init(g);
//         return;
//     }
//     g->time += dt;

//     // atualiza o player
//     player_update(&g->player, &g->map, &g->input, dt);

//     // atualiza o input
//     input_update(&g->input, &g->camera, &g->ui);

//     // atualiza a camera
//     camera_update(&g->camera, g->player.pos, g->input.move, dt);

//     // atualiza os veredins (sistema de órbita e seguimento)
//     for (auto& v : g->veredins) {
//         if (v->is_alive) {
//             veredim_update(v.get(), g->player.pos, dt);
//         }
//     }

//     // atualiza as criaturas
//     for (auto& c : g->creatures) {
//         if (c->is_alive) {
//             creature_update(c.get(), g->player.pos, dt);
//         }
//     }

//     // TEMPORARIO
//     if (g->input.throw_veredim) {
//         for (u32 i = 0; i < (u32)g->veredins.size(); i++) {
//             Veredim* v = (g->veredins)[i].get();
//             // só arremessa se ele estiver a seguir o player (disponível na órbita)
//             if (v->state == VEREDIM_FOLLOW) {
//                 v->state = VEREDIM_THROWN;
//                 v->state_timer = 0.0f;
                
//                 Vector2 diff = Vector2Subtract(g->input.mouse_pos, v->pos);
//                 v->vel = Vector2Scale(Vector2Normalize(diff), 750.0f);
                
//                 break; 
//             }
//         }
//     }

//     // remove as criaturas
//     for (int i = g->creatures.size() - 1; i >= 0; i--) {
//         Creature* c = g->creatures[i].get();
//         if (!c->is_alive) {
//             // remove o elemento na posição i
//             g->creatures.erase(g->creatures.begin() + i);
//         } else {
//             creature_update(c, g->player.pos, dt);
//         }
//     }

//     // sincroniza a ui
//     g->ui.score = g->wave * 100;
//     g->ui.veredim_count = (i32)g->veredins.size();
//     if (g->player.health <= 0) g->is_game_over = true;
// }

void game_update(Game* g, f32 dt) {
    if (g->is_game_over) {
        if (IsKeyPressed(KEY_R)) game_init(g);
        return;
    }
    g->time += dt;
    g->wave_timer += dt;

    // atualiza o input
    input_update(&g->input, &g->camera, &g->ui);
    
    // troca tipo selecionado
    if (g->input.switch_veredim_type) {
        u16 types[] = {
            ELEMENT_FIRE, ELEMENT_WATER, ELEMENT_PLANT, ELEMENT_ELECTRIC, 
            ELEMENT_EARTH, ELEMENT_ICE, ELEMENT_POISON, ELEMENT_METAL
        };
        for (i32 i = 0; i < 8; i++) {
            if (g->ui.selected_element == types[i]) {
                g->ui.selected_element = types[(i + 1) % 8]; // Rotaciona entre os 8
                break;
            }
        }
    }
    // atualiza player
    player_update(&g->player, &g->input, dt);
    
    // whistle
    if (g->input.whistle) {
        for (auto& v : g->veredins) {
            if (v->is_alive && Vector2Distance(v->pos, g->player.pos) < 150.0f) {
                v->state = VEREDIM_RETURN;
                v->is_carrying = false;
            }
        }
    }
    
    // arremessar veredim
    if (g->input.throw_veredim) {
        for (auto& v : g->veredins) {
            if (v->is_alive && v->state == VEREDIM_FOLLOW && v->element_mask == g->ui.selected_element) {
                Vector2 dir = Vector2Normalize(Vector2Subtract(g->input.mouse_pos, v->pos));
                v->vel = Vector2Scale(dir, 500.0f);
                v->state = VEREDIM_THROWN;
                v->state_timer = 0;
                break;
            }
        }
    }
    
    // atualiza veredims
    i32 alive_count = 0;
    for (auto& v : g->veredins) {
        if (!v->is_alive) continue;
        alive_count++;
        
        veredim_update(v.get(), g->player.pos, dt);
        
        // combate com criaturas
        if (v->state == VEREDIM_THROWN || v->state == VEREDIM_ATTACK) {
            for (auto& c : g->creatures) {
                if (!c->is_alive || c->state == CREATURE_EAT) continue;
                
                f32 dist = Vector2Distance(v->pos, c->pos);
                if (dist < v->radius + c->radius + 5.0f) {
                    if (v->state == VEREDIM_THROWN) {
                        v->state = VEREDIM_ATTACK;
                    }
                    
                    // aplica dano
                    f32 dmg = v->attack * dt;
                    dmg *= element_effectiveness(v->element_mask, c->element_mask);
                    c->health -= (i32)dmg;
                    
                    veredim_give_xp(v.get(), 1);
                    
                    if (c->health <= 0) {
                        veredim_give_xp(v.get(), 20 * c->level);
                        v->state = VEREDIM_RETURN;
                    }
                }
            }
        }
        
        // sistema de captura
        if (v->state == VEREDIM_CAPTURED) {
            for (auto& c : g->creatures) {
                if (!c->is_alive || !c->is_capturable) continue;
                
                f32 dist = Vector2Distance(v->pos, c->pos);
                if (dist < v->capture_radius) {
                    c->current_carriers++;
                    
                    if (c->current_carriers >= c->required_carriers) {
                        c->capture_progress += dt * 0.5f;
                        
                        if (c->capture_progress >= 1.0f) {
                            // captura completa!
                            auto new_v = std::make_unique<Veredim>();
                            veredim_init(new_v.get(), c->pos, c->element_mask);
                            new_v->level = c->level;
                            new_v->layer = (i32)(g->veredins.size() / 10);
                            new_v->orbit_angle = ((f32)g->veredins.size() * 0.5f);
                            g->veredins.push_back(std::move(new_v));
                            
                            g->ui.score += 100;
                            c->is_alive = false;
                            v->state = VEREDIM_RETURN;
                        }
                    }
                } else {
                    v->state = VEREDIM_RETURN;
                }
            }
        }
        
        // carregar objetos
        if (v->state == VEREDIM_FOLLOW) {
            for (size_t j = 0; j < g->objects.size(); j++) {
                Object* obj = g->objects[j].get();
                if (!obj->is_active || obj->is_delivered) continue;
                
                f32 dist = Vector2Distance(v->pos, obj->pos);
                if (dist < 40.0f && !v->is_carrying) {
                    v->state = VEREDIM_CARRY;
                    v->is_carrying = true;
                    v->carry_target_id = (i32)j;
                    obj->carriers++;
                    break;
                }
            }
        }
        
        // atualizar carregamento
        if (v->state == VEREDIM_CARRY && v->carry_target_id >= 0 && 
            v->carry_target_id < (i32)g->objects.size()) {
            Object* obj = g->objects[v->carry_target_id].get();
            
            if (obj && obj->is_active && !obj->is_delivered) {
                Vector2 to_base = Vector2Subtract(g->player.pos, obj->pos);
                f32 dist = Vector2Length(to_base);
                
                if (obj->carriers >= obj->weight) {
                    if (dist > 20.0f) {
                        obj->pos = Vector2Add(obj->pos, 
                            Vector2Scale(Vector2Normalize(to_base), 50.0f * dt));
                        v->pos = Vector2Add(obj->pos, Vector2{10, -10});
                    } else {
                        obj->is_delivered = true;
                        g->ui.score += obj->value;
                        veredim_give_xp(v.get(), obj->value);
                        v->state = VEREDIM_FOLLOW;
                        v->is_carrying = false;
                    }
                }
            } else {
                v->state = VEREDIM_RETURN;
                v->is_carrying = false;
            }
        }
    }
    
    g->ui.veredim_count = alive_count;
    
    // atualiza criaturas e comportamento de comer veredins
    for (size_t i = 0; i < g->creatures.size(); i++) {
        Creature* c = g->creatures[i].get();
        if (!c->is_alive) continue;
        
        // encontra veredim mais próximo
        Vector2 target_veredim_pos = g->player.pos;
        Veredim* closest_veredim = nullptr;
        f32 min_dist = 999999.0f;
        i32 closest_idx = -1;
        
        for (size_t j = 0; j < g->veredins.size(); j++) {
            Veredim* v = g->veredins[j].get();
            if (!v->is_alive || v->state == VEREDIM_DECEASED) continue;
            
            f32 dist = Vector2Distance(c->pos, v->pos);
            if (dist < min_dist) {
                min_dist = dist;
                target_veredim_pos = v->pos;
                closest_idx = (i32)j;
            }
        }
        
        creature_update(c, g->player.pos, target_veredim_pos, dt);
        
        // comportamento de comer veredim (estilo bulborb)
        if (c->state == CREATURE_CHASE_VEREDIM && closest_veredim) {
            f32 dist = Vector2Distance(c->pos, closest_veredim->pos);
            if (dist < c->radius) {
                c->state = CREATURE_EAT;
                c->eat_timer = 0;
                c->target_veredim_id = closest_idx;
                closest_veredim->state = VEREDIM_DECEASED;
            }
        }
        
        // enquanto come, o veredim morre
        if (c->state == CREATURE_EAT && c->target_veredim_id >= 0 && 
            c->target_veredim_id < (i32)g->veredins.size()) {
            Veredim* eaten = g->veredins[c->target_veredim_id].get();
            
            if (eaten->is_alive) {
                // outros veredims entram em pânico ao ver um sendo comido
                for (auto& v : g->veredins) {
                    if (v->is_alive && v.get() != eaten) {
                        f32 panic_dist = Vector2Distance(v->pos, c->pos);
                        if (panic_dist < 150.0f) {
                            v->panic_timer = 2.0f;
                        }
                    }
                }
            }
        }
        
        // ataca player
        if (c->state == CREATURE_ATTACK) {
            g->player.health -= (i32)(c->attack * dt * 0.5f);
        }
        
        // cria corpo ao morrer
        if (c->health <= 0 && c->is_alive) {
            c->is_alive = false;
            auto corpse = std::make_unique<Object>();
            object_init(corpse.get(), c->pos.x, c->pos.y, OBJECT_CORPSE);
            corpse->value = c->level * 10;
            g->objects.push_back(std::move(corpse));
        }
    }
    
    // remove criaturas mortas
    g->creatures.erase(
        std::remove_if(g->creatures.begin(), g->creatures.end(),
            [](const auto& c) { return !c->is_alive; }),
        g->creatures.end()
    );
    
    // remove veredins mortos
    g->veredins.erase(
        std::remove_if(g->veredins.begin(), g->veredins.end(),
            [](const auto& v) { return !v->is_alive; }),
        g->veredins.end()
    );
    
    // sistema de waves
    if (g->wave_timer > 30.0f) {
        g->wave++;
        g->wave_timer = 0;
        logic_spawn_creatures(g, 3 + g->wave);
        logic_spawn_objects(g, 5);
    }
    
    // atualiza câmera
    camera_update(&g->camera, g->player.pos, g->input.move, dt);
    
    // game over
    if (g->player.health <= 0) {
        g->player.is_alive = false;
        g->is_running = false;
    }
    
    ui_update(&g->ui, dt);
}

void game_render(Game* g) {
    BeginDrawing();
    g->background_color = GetColor(0x181818FF);
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

        // mira do mouse
        DrawCircleLinesV(g->input.mouse_pos, 8.0f, element_get_color(g->ui.selected_element));
      
        // área do whistle
        if (g->input.whistle) {
            DrawCircleV(g->input.mouse_pos, 150.0f, Fade(YELLOW, 0.3));
            DrawCircleLinesV(g->input.mouse_pos, 150.0f, YELLOW);
        }
    
    EndMode2D();

    // interface
    ui_draw(&g->ui, g->player.health, g->player.max_health, g->wave, g->time, !g->player.is_alive);

    EndDrawing();
}

void game_shutdown(Game* g) {
    UnloadFont(g->ui.font);
    UnloadImage(g->window_icon);
    map_shutdown(&g->map);
    CloseWindow();
}