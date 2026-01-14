#ifndef GAME_ELEMENTS_ELEMENT_H
#define GAME_ELEMENTS_ELEMENT_H

#include "game/core/types.h"

#include "raylib.h"

typedef enum Element {
    ELEMENT_NONE     = 0,
    ELEMENT_FIRE     = 1u << 0,
    ELEMENT_WATER    = 1u << 1,
    ELEMENT_PLANT    = 1u << 2,
    ELEMENT_ELECTRIC = 1u << 3,
    ELEMENT_EARTH    = 1u << 4,
    ELEMENT_ICE      = 1u << 5,
    ELEMENT_POISON   = 1u << 6,
    ELEMENT_METAL    = 1u << 7,
    ELEMENT_LIGHT    = 1u << 8
} Element;

Color element_get_color(u16 element_mask);
f32 element_effectiveness(u16 attacker, u16 defender);

#endif // GAME_ELEMENTS_ELEMENT_H