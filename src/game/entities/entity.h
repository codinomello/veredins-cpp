#ifndef GAME_ENTITIES_ENTITY
#define GAME_ENTITIES_ENTITY

#include "game/core/types.h"
#include "raylib.h"

typedef enum ElementType {
    ELEMENT_NONE     = 0, // bitmask (faz um bit shift de 1 bit para esquerda a cada elemento)
    ELEMENT_FIRE     = 1u << 0,
    ELEMENT_WATER    = 1u << 1,
    ELEMENT_PLANT    = 1u << 2,
    ELEMENT_ELECTRIC = 1u << 3,
    ELEMENT_EARTH    = 1u << 4,
    ELEMENT_ICE      = 1u << 5,
    ELEMENT_POISON   = 1u << 6,
    ELEMENT_LIGHT    = 1u << 7,
    ELEMENT_METAL    = 1u << 8,
    ELEMENT_WIND     = 1u << 9,
    ELEMENT_VOID     = 1u << 10,
    ELEMENT_MUSIC    = 1u << 11,
    ELEMENT_MAGMA    = 1u << 12,
    ELEMENT_LIFE     = 1u << 13,
    ELEMENT_GRAVITY  = 1u << 14,
    ELEMENT_COSMIC   = 1u << 15
} ElementType;

typedef struct Entity {
    // TODO: implementar estrutura Entity
} Entity;

Color entity_get_color(u16 element_mask);
bool element_is_strong(u16 a, u16 b);

#endif // GAME_ENTITIES_ENTITY