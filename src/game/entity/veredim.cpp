#include "game/entity/veredim.h"
#include "raylib.h"

void veredim_init(Veredim* v, f32 x, f32 y, u32 element) {
    v->id = 100;
    v->x = x;
    v->y = y;
    v->health = 60;
    v->max_health = 60;
    v->element = element;
    v->attack = 12;
    v->defense = 8;
}

void veredim_update(Veredim* v, f32 dt) {
    (void)dt;
    (void)v;
}

void veredim_draw(const Veredim* v) {
    DrawCircleV(
        (Vector2){ v->x, v->y },
        14.0f,
        GREEN
    );
    DrawText(
        TextFormat("HP: %d/%d", v->health, v->max_health),
        (int)v->x - 25,
        (int)v->y - 30,
        10,
        WHITE
    );
}