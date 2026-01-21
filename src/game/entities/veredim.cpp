#include <cmath>

#include "veredim.h"

#include "raymath.h"

void veredim_init(Veredim* v, Vector2 pos, u16 element) {
    *v = {
        .pos = pos,
        .vel = { 0, 0 },
        .radius = 5.5f,
        .capture_radius = 80.0f,
        .state_timer = 0.0f,
        .panic_timer = 0.0f,
        .health = 50,
        .max_health = 50,
        .attack = 10,
        .carry_target_id = -1,
        .xp = 0,
        .element_mask = element,
        .level = 1,
        .evolution_stage = 0,
        .is_alive = true,
        .is_carrying = false,
        .orbits = {
            { .radius = 40.0f, .capacity = 9, .current = 0 },  // camada interna
            { .radius = 75.0f, .capacity = 27, .current = 0 }, // camada média
            { .radius = 115.0f, .capacity = 81, .current = 0 } // camada externa
        },
        .state = VEREDIM_FOLLOW,
        .orbit = {
            .angle = 0.0f,
            .layer = 0,
            
        }
    };
}

void veredim_update(Veredim* v, Vector2 player_pos, f32 dt) {
    if (!v->is_alive) return;
    
    v->state_timer += dt;

    // diminui pânico ao longo do tempo
    if (v->panic_timer > 0) {
        v->panic_timer -= dt;
    }

    switch (v->state) {
        case VEREDIM_FOLLOW: {
            if (!v->is_alive || v->state != VEREDIM_FOLLOW) return;

            // Define os raios com base na camada salva na struct
            f32 dists[] = { 40.0f, 75.0f, 115.0f };
            f32 current_radius = dists[v->orbit.layer];

            // Faz as camadas de fora girarem levemente mais devagar
            f32 speed_multiplier = 1.0f - (v->orbit.layer * 0.2f);
            v->orbit.angle += 2.0f * speed_multiplier * dt;

            v->pos.x = player_pos.x + cosf(v->orbit.angle) * current_radius;
            v->pos.y = player_pos.y + sinf(v->orbit.angle) * current_radius;
        } break;
        
        case VEREDIM_THROWN: {
            v->pos = Vector2Add(v->pos, Vector2Scale(v->vel, dt));
            v->vel = Vector2Scale(v->vel, 0.95f);
            
            if (v->state_timer > 2.0f || Vector2Length(v->vel) < 50.0f) {
                v->state = VEREDIM_RETURN;
                v->state_timer = 0;
            }
        } break;
        
        case VEREDIM_ATTACK: {
            // estado de ataque - move-se em direção ao alvo
            // (lógica de alvo será gerenciada no game.cpp)
        } break;
        
        case VEREDIM_CARRY: {
            // estado de carregar objeto
            // (lógica de carregamento será gerenciada no game.cpp)
        } break;
        
        case VEREDIM_CAPTURED: {
            // estado de captura
            // (lógica será gerenciada no game.cpp)
        } break;
        
        case VEREDIM_RETURN: {
            const float dists[3] = { 40.0f, 75.0f, 115.0f };
            f32 r = dists[v->orbit.layer];
            
            // Alvo na órbita (onde ele DEVERIA estar agora)
            Vector2 target_orbit_pos = {
                player_pos.x + cosf(v->orbit.angle) * r,
                player_pos.y + sinf(v->orbit.angle) * r
            };

            // Move suavemente em direção ao lugar dele na órbita
            v->pos = Vector2Lerp(v->pos, target_orbit_pos, 10.0f * dt);

            // Se estiver perto o suficiente, volta a seguir normalmente
            if (Vector2Distance(v->pos, target_orbit_pos) < 10.0f) {
                v->state = VEREDIM_FOLLOW;
                v->state_timer = 0;
            }
        } break;
        
        case VEREDIM_DECEASED: {
            // sendo comido - não faz nada, só aguarda a morte
            v->health -= 50 * dt;
            if (v->health <= 0) {
                v->is_alive = false;
            }
        } break;
    }
}

void veredim_draw(const Veredim* v, f32 game_time) {
    if (!v->is_alive) return;
    
    Color color = element_get_color(v->element_mask);
    
    // aura pulsante
    f32 pulse = sinf(game_time * 4.0f + v->orbit.angle) * 2.0f;
    DrawCircleLinesV(v->pos, v->radius + 4.0f + pulse, ColorAlpha(color, 0.4f));
    
    // corpo
    DrawCircleV(v->pos, v->radius, color);
    
    // estrelas de evolução
    for (i32 i = 0; i < v->evolution_stage + 1; i++) {
        DrawCircleV(Vector2{v->pos.x - 6 + i * 6, v->pos.y - v->radius - 8}, 2, GOLD);
    }
    
    // barra de vida
    f32 hp_ratio = (f32)v->health / (f32)v->max_health;
    DrawRectangle(v->pos.x - 15, v->pos.y - v->radius - 15, 30, 3, BLACK);
    DrawRectangle(v->pos.x - 15, v->pos.y - v->radius - 15, (i32)(30 * hp_ratio), 3, LIME);
}

void veredim_check_evolution(Veredim* v) {
    i32 xp_needed = (v->evolution_stage + 1) * 100;
    
    if (v->xp >= xp_needed && v->evolution_stage < 2) {
        v->evolution_stage++;
        v->xp = 0;
        v->max_health += 30;
        v->health = v->max_health;
        v->attack += 10;
        v->radius += 1.5f;
    }
}

void veredim_give_xp(Veredim* v, i32 amount) {
    v->xp += amount;
    veredim_check_evolution(v);
}
