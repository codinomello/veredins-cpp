#ifndef GAME_ENTITIES_ENTITY
#define GAME_ENTITIES_ENTITY

#include "game/core/types.h"

#include "raylib.h"

typedef enum EntityType {
    ELEMENT_NONE     = 0,           // bitmask (faz um bit shift de 1 bit para esquerda a cada elemento)
    ELEMENT_FIRE     = 1u << 0,     // fogo
    ELEMENT_WATER    = 1u << 1,     // água
    ELEMENT_PLANT    = 1u << 2,     // planta
    ELEMENT_ELECTRIC = 1u << 3,     // elétrico
    ELEMENT_EARTH    = 1u << 4,     // terra
    ELEMENT_ICE      = 1u << 5,     // gelo
    ELEMENT_POISON   = 1u << 6,     // veneno
    ELEMENT_LIGHT    = 1u << 7      // luz
    // ELEMENT_METAL    = 1u << 8,  // metal
    // ELEMENT_WIND     = 1u << 9,  // vento
    // ELEMENT_VOID     = 1u << 10, // vácuo
    // ELEMENT_MUSIC    = 1u << 11, // música
    // ELEMENT_MAGMA    = 1u << 12, // magma
    // ELEMENT_LIFE     = 1u << 13, // vida
    // ELEMENT_GRAVITY  = 1u << 14, // gravidade
    // ELEMENT_COSMIC   = 1u << 15  // cósmico
} EntityType;

typedef struct Entity {
    // TODO: implementar estrutura Entity
    EntityType type;
} Entity;

Color entity_get_color(u16 element);
bool element_is_strong(u16 a, u16 b);

#endif // GAME_ENTITIES_ENTITY