#ifndef GAME_ENTITY_ELEMENT_H
#define GAME_ENTITY_ELEMENT_H

typedef enum ElementType {
    ELEMENT_NONE     = 0, // Bitmask (faz um bit shift de 1 bit para esquerda a cada elemento)
    ELEMENT_FIRE     = 1u << 0,
    ELEMENT_WATER    = 1u << 1,
    ELEMENT_PLANT    = 1u << 2,
    ELEMENT_ELECTRIC = 1u << 3,
    ELEMENT_EARTH    = 1u << 4,
    ELEMENT_ICE      = 1u << 5
} ElementType;

#endif // GAME_ENTITY_ELEMENT_H