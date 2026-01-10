#ifndef GAME_ENTITY_VEREDIM_H
#define GAME_ENTITY_VEREDIM_H

#include "../core/types.h"
#include "raylib.h"

typedef enum VeredimElementType {
    ELEMENT_NONE     = 0, // Bitmask (faz um bit shift de 1 bit para esquerda a cada elemento)
    ELEMENT_FIRE     = 1 << 0,
    ELEMENT_WATER    = 1 << 1,
    ELEMENT_PLANT    = 1 << 2,
    ELEMENT_ELECTRIC = 1 << 3,
    ELEMENT_EARTH    = 1 << 4,
    ELEMENT_ICE      = 1 << 5
} VeredimElementType;

typedef enum VeredimState {
    VEREDIM_IDLE,
    VEREDIM_FOLLOWING,
    VEREDIM_ATTACKING,
    VEREDIM_DECEASED
} VeredimState;

typedef struct Veredim {
    u32 id;
    Vector2 pos;
    Vector2 target_pos;
    i32 health;
    i32 max_health;
    u32 element;
    i32 attack;
    i32 defense;
    f32 radius;
    f32 angle; // Em graus
    f32 orbit_radius;
    f32 orbit_speed; // Em graus por segundo
    VeredimState state;
} Veredim;

Veredim veredim_init(Veredim* veredim, f32 x, f32 y, u32 element);
void veredim_update(Veredim* veredim, f32 dt, f32 target_x, f32 target_y, u32 index);
Color veredim_get_color(u32 element);
void veredim_draw(const Veredim* veredim);

#endif // GAME_ENTITY_VEREDIM_H