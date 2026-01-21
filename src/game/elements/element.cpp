#include "element.h"

Color element_get_color(u16 elem_mask) {
    if (elem_mask & ELEMENT_FIRE)     return RED;
    if (elem_mask & ELEMENT_WATER)    return BLUE;
    if (elem_mask & ELEMENT_PLANT)    return GREEN;
    if (elem_mask & ELEMENT_ELECTRIC) return YELLOW;
    if (elem_mask & ELEMENT_EARTH)    return BROWN;
    if (elem_mask & ELEMENT_ICE)      return SKYBLUE;
    if (elem_mask & ELEMENT_POISON)   return PURPLE;
    if (elem_mask & ELEMENT_METAL)    return DARKGRAY;
    if (elem_mask & ELEMENT_LIGHT)    return GOLD;
    return GRAY;
}

f32 element_effectiveness(u16 attacker, u16 defender) {
    // vantagens (2.0x)
    if ((attacker & ELEMENT_FIRE)     && (defender & ELEMENT_PLANT))    return 2.0f;
    if ((attacker & ELEMENT_FIRE)     && (defender & ELEMENT_ICE))      return 2.0f;
    if ((attacker & ELEMENT_WATER)    && (defender & ELEMENT_FIRE))     return 2.0f;
    if ((attacker & ELEMENT_WATER)    && (defender & ELEMENT_EARTH))    return 2.0f;
    if ((attacker & ELEMENT_PLANT)    && (defender & ELEMENT_WATER))    return 2.0f;
    if ((attacker & ELEMENT_ELECTRIC) && (defender & ELEMENT_WATER))    return 2.0f;
    if ((attacker & ELEMENT_ICE)      && (defender & ELEMENT_PLANT))    return 2.0f;
    if ((attacker & ELEMENT_EARTH)    && (defender & ELEMENT_ELECTRIC)) return 2.0f;
    
    // desvantagens (0.5x)
    if ((attacker & ELEMENT_FIRE)     && (defender & ELEMENT_WATER))    return 0.5f;
    if ((attacker & ELEMENT_WATER)    && (defender & ELEMENT_PLANT))    return 0.5f;
    if ((attacker & ELEMENT_PLANT)    && (defender & ELEMENT_FIRE))     return 0.5f;
    if ((attacker & ELEMENT_ELECTRIC) && (defender & ELEMENT_EARTH))    return 0.5f;
    
    return 1.0f;
}