#include <cmath>

#include "game/entity/veredim.h"
#include "game/core/math.h"
#include "raylib.h"

Veredim veredim_init(Veredim* v, f32 x, f32 y, u32 element) {
    return (Veredim) {
        v->id = 0,
        v->pos = {
            x, y
        },
        v->target_pos = {
            x, y
        },
        v->health = 60,
        v->max_health = 60,
        v->element = element,
        v->attack = 12,
        v->defense = 8,
        v->state = VEREDIM_FOLLOWING
    };
}

void veredim_update(Veredim* v, f32 dt, f32 target_x, f32 target_y, u32 index) {
    if (v->state != VEREDIM_FOLLOWING) {
        return;
    }
    f32 dx = target_x - v->pos.x;
    f32 dy = target_y - v->pos.y;

    f32 len = std::sqrt(dx * dx + dy * dy);
    if (len > 1.0f) {
        dx /= len;
        dy /= len;
        v->pos.x += dx * 120.0f * dt;
        v->pos.y += dy * 120.0f * dt;
    }

    switch (v->state) {
        case VEREDIM_IDLE:
            break;
        case VEREDIM_FOLLOWING:
            f64 angle = index * 0.3f + GetTime();
            Vector2 offset = {
                cosf((f32)angle) * 30.0f,
                sinf((f32)angle) * 30.0f 
            };
            v->target_pos = vector2_add(v->pos, offset);
            v->pos = vector2_lerp(v->pos, v->target_pos, 5.0f * dt);
            break;
    }
}

Color veredim_get_color(u32 element) {
    switch (element) {
    case ELEMENT_FIRE:
        return RED;
    case ELEMENT_WATER:
        return BLUE;
    case ELEMENT_PLANT:
        return GREEN;
    case ELEMENT_ELECTRIC:
        return YELLOW;
    case ELEMENT_EARTH:
        return BROWN;
    case ELEMENT_ICE:
        return SKYBLUE;
    default:
        return GRAY;
        break;
    }
}

void veredim_draw(const Veredim* v) {
    DrawCircleV(
        v->pos,
        14.0f,
        veredim_get_color(v->element)
    );
    DrawText(
        TextFormat("HP: %d/%d", v->health, v->max_health),
        (int)v->pos.x - 25,
        (int)v->pos.y - 30,
        10,
        WHITE
    );
}