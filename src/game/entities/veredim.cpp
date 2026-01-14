#include <cmath>

#include "veredim.h"

#include "raymath.h"

void veredim_init(Veredim* v, Vector2 pos, u16 element) {
    *v = {
        .pos = pos,
        .vel = { 0, 0 },
        .radius = 5.5f,
        .capture_radius = 80.0f,
        .orbit_angle = 0.0f,
        .state_timer = 0.0f,
        .panic_timer = 0.0f,
        .health = 50,
        .max_health = 50,
        .attack = 10,
        .carry_target_id = -1,
        .xp = 0,
        .element_mask = element,
        .level = 1,
        .layer = 0,
        .evolution_stage = 0,
        .is_alive = true,
        .is_carrying = false,
        .state = VEREDIM_FOLLOW
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
            // movimento de órbita ao redor do player
        f32 orbit_radius = (v->layer == 0) ? 40.0f : 80.0f;
        
        // Velocidade de rotação (ajuste o 2.0f para girar mais rápido ou devagar)
        v->orbit_angle += 2.0f * dt; 

        // Cálculo da posição usando coordenadas polares (Conserta a espiral)
        v->pos.x = player_pos.x + cosf(v->orbit_angle) * orbit_radius;
        v->pos.y = player_pos.y + sinf(v->orbit_angle) * orbit_radius;
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
            v->pos = Vector2MoveTowards(v->pos, player_pos, 200.0f * dt);
            if (Vector2Distance(v->pos, player_pos) < 30.0f) {
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
    f32 pulse = sinf(game_time * 4.0f + v->orbit_angle) * 2.0f;
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
