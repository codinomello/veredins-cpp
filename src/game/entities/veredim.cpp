#include <cmath>

#include "game/core/math.h"
#include "veredim.h"
#include "raylib.h"

void veredim_init(Veredim* v, f32 x, f32 y, u32 element_mask) {
    *v = (Veredim) {
        .position = {
            x, y
        },
        .target = {
            x, y
        },
        .velocity = {
            1.0f, 1.0f
        },
        .size = {
            16.0f, 16.0f
        },
        .speed        = 80.0f,
        .radius       = 8.0f,
        .angle        = 0.0f,
        .orbit_speed  = 1.0f,
        .orbit_radius = 90.0f,
        .attack_cooldown = 0.6f,
        .attack_timer   = 0.0f,
        .health       = 60,
        .max_health   = 60,
        .attack       = 12,
        .defense      = 8,
        .id           = 0,
        .element_mask = element_mask,
        .state        = VEREDIM_FOLLOW,
        .is_alive     = true
    };
}

void veredim_follow(Veredim* v, Player* p, u32 index, f32 dt) {
    if (v->state != VEREDIM_FOLLOW) {
        return;
    }

   if (v->state != VEREDIM_FOLLOW) {
        return;
    }

    f32 time = (f32)GetTime() * v->orbit_speed + (f32)index;

    v->target.x = p->position.x + cosf(time) * v->orbit_radius;
    v->target.y = p->position.y + sinf(time) * v->orbit_radius;

    v->position.x = lerp(v->position.x, v->target.x, 6.0f * dt);
    v->position.y = lerp(v->position.y, v->target.y, 6.0f * dt);
}

void veredim_attack(Veredim* v, Creature* c, f32 dt) {
    if (!c || !c->is_alive) {
        v->state = VEREDIM_RETURN;
        return;
    }

    // gruda no inimigo
    Vector2 dir = vector2_normalize(vector2_subtract(c->position, v->position));
    v->position = vector2_add(v->position, vector2_scale(dir, 100.0f * dt));

    // dano por segundo
    f32 dmg = v->attack * dt;

    if (veredim_element_is_strong(v->element_mask, c->element_mask)) {
        dmg *= 2.0f;
    }

    c->health -= dmg;

    if (c->health <= 0.0f) {
        c->is_alive = false;
        v->state = VEREDIM_RETURN;
    }
}

void veredim_update(Veredim* v, Player* p, Creature* c, u32 index, f32 dt) {
    switch (v->state) {
        case VEREDIM_FOLLOW:
            veredim_follow(v, p, index, dt);
            break;

        case VEREDIM_ATTACK:
            veredim_attack(v, c, dt);
            break;

        case VEREDIM_STUN:
            v->velocity.x = 0.0f;
            v->velocity.y = 0.0f;
            break;

        case VEREDIM_IDLE:
        default:
            // não faz nada
            break;
    }
}

Color veredim_get_color(u32 element_mask) {
    if (element_mask & ELEMENT_FIRE)     return RED;
    if (element_mask & ELEMENT_WATER)    return BLUE;
    if (element_mask & ELEMENT_PLANT)    return GREEN;
    if (element_mask & ELEMENT_ELECTRIC) return YELLOW;
    if (element_mask & ELEMENT_EARTH)    return BROWN;
    if (element_mask & ELEMENT_ICE)      return SKYBLUE;

    return GRAY;
}

void veredim_draw(const Veredim* v) {
    Color base_color = veredim_get_color(v->element_mask);

    f32 time  = (f32)GetTime();
    f32 pulse = sinf(time * 3.0f + (v->position.x * 0.1f)) * 2.0f;

    Color aura_color = ColorAlpha(base_color, 0.6f);
    DrawCircleLinesV(v->position, v->radius + 6.0f + pulse, aura_color);

    DrawCircleV(v->position, v->radius + 1.0f, BLACK);
    DrawCircleV(v->position, v->radius, base_color);

    DrawCircleV(
        (Vector2){ v->position.x - 2.0f, v->position.y - 2.0f },
        v->radius * 0.3f,
        ColorAlpha(WHITE, 0.5f)
    );

    f32 health_bar_width = 30.0f;
    f32 health_percent   = (f32)v->health / (f32)v->max_health;

    Vector2 bar_pos = {
        v->position.x - health_bar_width * 0.5f,
        v->position.y - v->radius - 15.0f
    };

    DrawRectangleV(bar_pos, (Vector2) {
        health_bar_width, 4.0f
    }, ColorAlpha(BLACK, 0.8f));

    DrawRectangleV(bar_pos, (Vector2) {
        health_bar_width * health_percent,
        4.0f
    }, LIME);

    DrawText(
        TextFormat("%d/%d", v->health, v->max_health),
        (u32)(v->position.x - 12),
        (u32)(v->position.y - v->radius - 26),
        10,
        WHITE
    );
}

bool veredim_element_is_strong(u32 a, u32 b) {
    if ((a & ELEMENT_FIRE) && (b & ELEMENT_PLANT)) return true;
    if ((a & ELEMENT_WATER) && (b & ELEMENT_FIRE)) return true;
    if ((a & ELEMENT_PLANT) && (b & ELEMENT_WATER)) return true;
    if ((a & ELEMENT_ELECTRIC) && (b & ELEMENT_WATER)) return true;
    if ((a & ELEMENT_ICE) && (b & ELEMENT_PLANT)) return true;
    if ((a & ELEMENT_EARTH) && (b & ELEMENT_ELECTRIC)) return true;
    if ((a & ELEMENT_ICE) && (b & ELEMENT_FIRE)) return true;
    if ((a & ELEMENT_FIRE) && (b & ELEMENT_ICE)) return true;
    return false;
}