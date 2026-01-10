#ifndef GAME_ENTITY_CREATURE_H
#define GAME_ENTITY_CREATURE_H

#include "../core/types.h"

typedef enum CreatureType {
    CREATURE_TYPE_NPC,
    CREATURE_TYPE_MONSTER,
    CREATURE_TYPE_BOSS
} CreatureType;

typedef struct Creature {
    u32 id;
    f32 x;
    f32 y;
    i32 health;
    i32 max_health;
    i32 attack;
    i32 defense;
    CreatureType type;
} Creature;

#endif // GAME_ENTITY_CREATURE_H