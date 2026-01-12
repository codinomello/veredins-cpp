#include "creature.h"
#include "raymath.h"

void creature_init(Creature* c, f32 x, f32 y) {
    *c = {
        .pos = { x, y },
        .radius = 15.0f,
        .speed = 60.0f,
        .health = 50,
        .max_health = 50,
        .attack = 10,
        .element_mask = ELEMENT_NONE,
        .state = CREATURE_IDLE,
        .is_alive = true // Certifique-se que este campo existe no struct
    };
}

void creature_update(Creature* c, f32 dt, Vector2 player_pos) {
    if (!c->is_alive || c->state == CREATURE_DEAD) return;

    // 1. Lógica de Distância Simplificada
    f32 dist = Vector2Distance(c->pos, player_pos);

    if (dist < 250.0f) { // Raio de detecção
        c->state = CREATURE_CHASE;
    } else {
        c->state = CREATURE_IDLE;
    }

    // 2. Movimento Suave (MoveTowards substitui toda a matemática de dx/dy/sqrt)
    if (c->state == CREATURE_CHASE) {
        // Move em direção ao player sem ultrapassar a velocidade máxima
        c->pos = Vector2MoveTowards(c->pos, player_pos, c->speed * dt);
    }
}

void creature_draw(const Creature* c) {
    if (!c->is_alive) return;

    // Desenha o corpo com contorno para combinar com o Player/Veredins
    DrawCircleV(c->pos, c->radius + 1.0f, BLACK);
    DrawCircleV(c->pos, c->radius, PURPLE); // Mudei para Roxo para diferenciar do HP

    // Barra de Vida Simplificada
    f32 hp_ratio = (f32)c->health / (f32)c->max_health;
    Vector2 bar_size = { 30.0f, 4.0f };
    Vector2 bar_pos = { c->pos.x - bar_size.x/2, c->pos.y - c->radius - 12.0f };

    DrawRectangleV(bar_pos, bar_size, ColorAlpha(BLACK, 0.5f)); // Fundo
    DrawRectangleV(bar_pos, { bar_size.x * hp_ratio, bar_size.y }, RED); // Vida
}