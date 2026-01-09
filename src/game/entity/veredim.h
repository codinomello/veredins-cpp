#ifndef GAME_ENTITY_CREATURE_H
#define GAME_ENTITY_CREATURE_H

#include "game/core/types.h"

typedef enum VeredimElementType {
    ELEMENT_NONE     = 0, // Bitmask (faz um bit shift de 1 bit para esquerda a cada elemento)
    ELEMENT_FIRE     = 1 << 0,
    ELEMENT_WATER    = 1 << 1,
    ELEMENT_PLANT    = 1 << 2,
    ELEMENT_ELECTRIC = 1 << 3,
    ELEMENT_EARTH    = 1 << 4,
    ELEMENT_ICE      = 1 << 5
} VeredimElementType;

typedef struct Veredim {
    u32 id;

    f32 x;
    f32 y;

    i32 health;
    i32 max_health;

    u32 element;

    i32 attack;
    i32 defense;
} Veredim;

void veredim_init(Veredim* v, f32 x, f32 y, u32 element_mask);
void veredim_update(Veredim* v, f32 dt);
void veredim_draw(const Veredim* v);

#endif // GAME_ENTITY_CREATURE_H