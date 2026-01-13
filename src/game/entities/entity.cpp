#include "entity.h"

Color entity_get_color(u16 element_mask) {
    if (element_mask == ELEMENT_NONE)    return GRAY;       // nenhum
    if (element_mask & ELEMENT_FIRE)     return RED;        // fogo
    if (element_mask & ELEMENT_WATER)    return BLUE;       // água
    if (element_mask & ELEMENT_PLANT)    return GREEN;      // planta
    if (element_mask & ELEMENT_ELECTRIC) return YELLOW;     // elétrico
    if (element_mask & ELEMENT_EARTH)    return BROWN;      // terra
    if (element_mask & ELEMENT_ICE)      return SKYBLUE;    // gelo
    if (element_mask & ELEMENT_POISON)   return PURPLE;     // veneno
    if (element_mask & ELEMENT_LIGHT)    return GOLD;       // luz
    // if (element_mask & ELEMENT_METAL)    return DARKGRAY;   // metal
    // if (element_mask & ELEMENT_WIND)     return BEIGE;      // vento
    // if (element_mask & ELEMENT_VOID)     return BLACK;      // vácuo
    // if (element_mask & ELEMENT_MUSIC)    return MAGENTA;    // música
    // if (element_mask & ELEMENT_MAGMA)    return ORANGE;     // magma 
    // if (element_mask & ELEMENT_LIFE)     return PINK;       // vitalidade
    // if (element_mask & ELEMENT_GRAVITY)  return DARKPURPLE; // gravidade
    // if (element_mask & ELEMENT_COSMIC)   return DARKBLUE;   // cósmico

    return GRAY;
}

bool element_is_strong(u16 a, u16 b) {
    // vantagens básicas
    if ((a & ELEMENT_FIRE)     && (b & ELEMENT_PLANT))    return true;
    if ((a & ELEMENT_WATER)    && (b & ELEMENT_FIRE))     return true;
    if ((a & ELEMENT_PLANT)    && (b & ELEMENT_WATER))    return true;
    if ((a & ELEMENT_ELECTRIC) && (b & ELEMENT_WATER))    return true;
    if ((a & ELEMENT_EARTH)    && (b & ELEMENT_ELECTRIC)) return true;
    if ((a & ELEMENT_ICE)      && (b & ELEMENT_PLANT))    return true;

    return false;
}