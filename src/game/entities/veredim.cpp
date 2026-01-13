#include <cmath>

#include "veredim.h"
#include "raymath.h"

void veredim_init(Veredim* v, f32 x, f32 y, u16 element) {
    *v = {
        .pos = { x, y },
        .vel = { 0, 0 },
        .radius = 5.5f,
        .orbit_angle = 0,
        .state_timer = 0,
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

void veredim_update(Veredim* v, Player* p, u32 total_count, u32 index, f32 dt) {
if (!v->is_alive) return;
    v->state_timer += dt;
    switch (v->state) {
        case VEREDIM_FOLLOW: {
            // órbita com camadas
            f32 orbit_radius = 50.0f + (v->layer * 25.0f);
            f32 angle_step = (2.0f * PI) / (f32)total_count;
            v->orbit_angle = (f32)index * angle_step + (v->state_timer * 1.5f);
            
            Vector2 target = {
                p->pos.x + cosf(v->orbit_angle) * orbit_radius,
                p->pos.y + sinf(v->orbit_angle) * orbit_radius
            };
            v->pos = Vector2Lerp(v->pos, target, 8.0f * dt);
        } break;
        case VEREDIM_THROWN: {
            v->pos = Vector2Add(v->pos, Vector2Scale(v->vel, dt));
            v->vel = Vector2Scale(v->vel, 0.95f); // fricção
            
            if (v->state_timer > 2.0f) {
                v->state = VEREDIM_RETURN;
            }
        } break;
        case VEREDIM_RETURN: {
            v->pos = Vector2MoveTowards(v->pos, p->pos, 200.0f * dt);
            if (Vector2Distance(v->pos, p->pos) < 30.0f) {
                v->state = VEREDIM_FOLLOW;
                v->state_timer = 0;
            }
        } break;
    }
}

void veredim_draw(const Veredim* v, f32 game_time) {
    if (!v->is_alive) return;
    
    Color color = entity_get_color(v->element_mask);
    
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
