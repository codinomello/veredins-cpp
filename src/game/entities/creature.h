#ifndef GAME_ENTITIES_CREATURE_H
#define GAME_ENTITIES_CREATURE_H

#include "game/core/types.h"
#include "entity.h"

typedef enum CreatureState : u8 {
    CREATURE_IDLE,
    CREATURE_WANDER,
    CREATURE_CHASE,
    CREATURE_ATTACK,
    CREATURE_FLEE,
    CREATURE_CAPTURE,
    CREATURE_DEAD
} CreatureState;

typedef struct Creature {
    Vector2 pos;
    Vector2 vel;
    f32 radius;
    f32 speed;
    f32 flee_timer;
    f32 capture_progress;
    i32 health;
    i32 max_health;
    u32 attack;
    u32 required_carriers;
    u32 current_carriers;
    u16 element_mask;
    u8 level;
    bool is_alive;
    bool is_capturable;   // pode ser capturada quando vida < 30%
    CreatureState state;
} Creature;

void creature_init(Creature* c, f32 x, f32 y, u16 element, u8 level);
void creature_update(Creature* c, f32 dt, Vector2 player_pos);
void creature_draw(const Creature* c);

#endif // GAME_ENTITIES_CREATURE_H