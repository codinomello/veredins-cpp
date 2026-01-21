#include "game/elements/element.h"
#include "creature.h"

#include "raymath.h"

void creature_init(Creature* c, Vector2 pos, u16 element, u8 level) {
    *c = {
        .pos = pos,
        .vel = {0, 0},
        .radius = 12.0f + level * 2.0f,
        .detection_radius = 200.0f + level * 20.0f,
        .speed = 80.0f + level * 5.0f,
        .eat_timer = 0.0f,
        .flee_timer = 0.0f,
        .capture_progress = 0.0f,
        .health = 50 + level * 20,
        .max_health = 50 + level * 20,
        .target_veredim_id = -1,
        .attack = (u32)5 + level * (u32)3,
        .required_carriers = (u32)2 + level,
        .current_carriers = 0,
        .element_mask = element,
        .level = level,
        .is_alive = true,
        .is_capturable = false,
        .state = CREATURE_WANDER
    };
}

void creature_update(Creature* c, Vector2 player_pos, Vector2 veredim_pos, f32 dt) {
    if (!c->is_alive) return;
    
    f32 dist_to_player = Vector2Distance(c->pos, player_pos);
    f32 dist_to_veredim = Vector2Distance(c->pos, veredim_pos);
    c->is_capturable = (c->health < c->max_health * 0.3f);
    c->current_carriers = 0;
    
    switch (c->state) {
        case CREATURE_IDLE:
        case CREATURE_WANDER: {
            // movimento aleatório
            if ((i32)(GetTime() * 2) % 3 == 0) {
                c->vel.x = (f32)(rand() % 3 - 1);
                c->vel.y = (f32)(rand() % 3 - 1);
                if (Vector2Length(c->vel) > 0) {
                    c->vel = Vector2Scale(Vector2Normalize(c->vel), c->speed * 0.5f);
                }
            }
            c->pos = Vector2Add(c->pos, Vector2Scale(c->vel, dt));
            
            // prioriza veredim se estiver perto (como bulborb)
            if (dist_to_veredim < c->detection_radius * 0.7f) {
                c->state = CREATURE_CHASE_VEREDIM;
                c->target_veredim_id = 0; // será atualizado no game.cpp
            } else if (dist_to_player < c->detection_radius) {
                c->state = CREATURE_CHASE_PLAYER;
            }
        } break;
        
        case CREATURE_CHASE_VEREDIM: {
            // persegue veredim para comer (comportamento bulborb)
            Vector2 dir = Vector2Normalize(Vector2Subtract(veredim_pos, c->pos));
            c->pos = Vector2Add(c->pos, Vector2Scale(dir, c->speed * 1.2f * dt));
            
            // se alcançou o veredim, começa a comer
            if (dist_to_veredim < c->radius) {
                c->state = CREATURE_EAT;
                c->eat_timer = 0;
            }
            
            // se veredim fugiu muito, volta a vagar
            if (dist_to_veredim > c->detection_radius * 1.5f) {
                c->state = CREATURE_WANDER;
                c->target_veredim_id = -1;
            }
        } break;
        
        case CREATURE_EAT: {
            // comendo veredim (fica parado por 2 segundos)
            c->eat_timer += dt;
            c->vel = {0, 0};
            
            if (c->eat_timer >= 2.0f) {
                // terminou de comer, volta a vagar
                c->state = CREATURE_WANDER;
                c->eat_timer = 0;
                c->target_veredim_id = -1;
                
                // recupera vida ao comer
                c->health += 20;
                if (c->health > c->max_health) c->health = c->max_health;
            }
        } break;
        
        case CREATURE_CHASE_PLAYER: {
            Vector2 dir = Vector2Normalize(Vector2Subtract(player_pos, c->pos));
            c->pos = Vector2Add(c->pos, Vector2Scale(dir, c->speed * dt));
            
            // se veredim aparecer perto, muda prioridade
            if (dist_to_veredim < c->detection_radius * 0.5f) {
                c->state = CREATURE_CHASE_VEREDIM;
            }
            
            if (dist_to_player < c->radius + 15.0f) {
                c->state = CREATURE_ATTACK;
            }
            
            if (c->is_capturable) {
                c->state = CREATURE_FLEE;
                c->flee_timer = 0;
            }
        } break;
        
        case CREATURE_ATTACK: {
            if (dist_to_player > c->radius + 20.0f) {
                c->state = CREATURE_CHASE_PLAYER;
            }
        } break;
        
        case CREATURE_FLEE: {
            c->flee_timer += dt;
            Vector2 dir = Vector2Normalize(Vector2Subtract(c->pos, player_pos));
            c->pos = Vector2Add(c->pos, Vector2Scale(dir, c->speed * 1.5f * dt));
            
            if (c->flee_timer > 3.0f && dist_to_player > 250.0f) {
                c->state = CREATURE_IDLE;
            }
        } break;
    }
    
    if (c->health <= 0) {
        c->is_alive = false;
        c->state = CREATURE_DECEASED;
    }
}

void creature_draw(const Creature* c) {
    if (!c->is_alive) return;
    
    Color color = element_get_color(c->element_mask);
    
    // sombra
    DrawCircleV(Vector2{c->pos.x + 2, c->pos.y + 2}, c->radius, ColorAlpha(BLACK, 0.3f));
    
    // corpo
    DrawCircleV(c->pos, c->radius + 1, BLACK);
    DrawCircleV(c->pos, c->radius, color);
    
    // se comendo, desenha boca aberta
    if (c->state == CREATURE_EAT) {
        f32 mouth_size = c->radius * 0.6f;
        Vector2 mouth_pos = {c->pos.x + c->radius * 0.3f, c->pos.y};
        DrawCircleV(mouth_pos, mouth_size, BLACK);
    }
    
    // indicador de estado
    if (c->state == CREATURE_CHASE_PLAYER || c->state == CREATURE_CHASE_VEREDIM) {
        DrawCircleLinesV(c->pos, c->radius + 4, RED);
    } else if (c->is_capturable) {
        DrawCircleLinesV(c->pos, c->radius + 4, YELLOW);
        
        if (c->capture_progress > 0) {
            DrawRectangle(c->pos.x - 20, c->pos.y - c->radius - 15, 40, 5, DARKGRAY);
            DrawRectangle(c->pos.x - 20, c->pos.y - c->radius - 15, 
                         (i32)(40 * c->capture_progress), 5, GREEN);
        }
    }
    
    // barra de vida
    f32 hp_ratio = (f32)c->health / (f32)c->max_health;
    DrawRectangle(c->pos.x - 15, c->pos.y - c->radius - 8, 30, 3, BLACK);
    DrawRectangle(c->pos.x - 15, c->pos.y - c->radius - 8, 
                 (i32)(30 * hp_ratio), 3, hp_ratio > 0.3f ? LIME : RED);
}