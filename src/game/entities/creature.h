#ifndef GAME_ENTITIES_CREATURE_H
#define GAME_ENTITIES_CREATURE_H

#include "../element/element.h"
#include "../core/types.h"
#include "raylib.h"

typedef enum CreatureState {
    CREATURE_IDLE,
    CREATURE_WANDER,
    CREATURE_CHASE,
    CREATURE_ATTACK,
    CREATURE_DEAD
} CreatureState;

typedef struct Creature {
    Vector2 position;
    Vector2 velocity;
    f32 radius;
    f32 speed;
    f32 attack_cooldown;
    f32 attack_timer;
    i32 health;
    i32 max_health;
    u32 attack;
    u32 id;
    u32 element_mask;
    CreatureState state;
} Creature;

void creature_init(Creature* c, f32 x, f32 y);
void creature_update(Creature* c, f32 dt, Vector2 player_pos);
void creature_draw(const Creature* c);

#endif // GAME_ENTITIES_CREATURE_H