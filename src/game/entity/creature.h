#ifndef GAME_ENTITY_CREATURE_H
#define GAME_ENTITY_CREATURE_H

#include "game/core/types.h"

typedef enum CreatureType {
    CREATURE_TYPE_NPC,
    CREATURE_TYPE_MONSTER,
    CREATURE_TYPE_BOSS
} CreatureType;

typedef struct Creature {
    u32 id;
} Creature;

#endif // GAME_ENTITY_CREATURE_H