#include "creature.h"
#include <math.h>

void creature_init(Creature* c, f32 x, f32 y) {
    *c = (Creature) {
        .position = { x, y },
        .velocity = { 0.0f, 0.0f },
        .radius = 15.0f,
        .speed = 60.0f,
        .attack_cooldown = 1.5f,
        .attack_timer = 0.0f,
        .health = 50,
        .max_health = 50,
        .attack = 10,
        .id = 0,
        .element_mask = ELEMENT_NONE,
        .state = CREATURE_IDLE
    };
}

void creature_update(Creature* c, f32 dt, Vector2 player_pos) {
    if (c->state == CREATURE_DEAD) return;

    // distância ao player
    f32 dx = player_pos.x - c->position.x;
    f32 dy = player_pos.y - c->position.y;
    f32 dist2 = dx*dx + dy*dy;

    if (dist2 < 200.0f * 200.0f) {
        c->state = CREATURE_CHASE;
    } else {
        c->state = CREATURE_IDLE;
    }

    if (c->state == CREATURE_CHASE) {
        f32 len = sqrtf(dist2);
        if (len > 0.01f) {
            c->velocity.x = (dx / len) * c->speed;
            c->velocity.y = (dy / len) * c->speed;
        }
    } else {
        c->velocity.x = 0;
        c->velocity.y = 0;
    }

    c->position.x += c->velocity.x * dt;
    c->position.y += c->velocity.y * dt;
}

void creature_draw(const Creature* c) {
    if (c->state == CREATURE_DEAD) return;

    DrawCircleV(c->position, c->radius, RED);

    // vida
    float hp = (float)c->health / (float)c->max_health;
    DrawRectangle(
        (int)(c->position.x - 12),
        (int)(c->position.y - c->radius - 10),
        (int)(24 * hp),
        3,
        LIME
    );
}
