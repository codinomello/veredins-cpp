#ifndef GAME_ENTITIES_CREATURE_H
#define GAME_ENTITIES_CREATURE_H

#include "game/core/types.h"

typedef enum CreatureState : u8 {
    CREATURE_IDLE,
    CREATURE_WANDER,
    CREATURE_CHASE_PLAYER,
    CREATURE_CHASE_VEREDIM,
    CREATURE_ATTACK,
    CREATURE_EAT,
    CREATURE_FLEE,
    CREATURE_CAPTURED,
    CREATURE_DECEASED
} CreatureState;

typedef struct Creature {
    Vector2 pos;
    Vector2 vel;
    f32 radius;
    f32 detection_radius;
    f32 speed;
    f32 eat_timer;
    f32 flee_timer;
    f32 capture_progress;
    i32 health;
    i32 max_health;
    i32 target_veredim_id; // id do veredim sendo perseguido/comido
    u32 attack;
    u32 required_carriers;
    u32 current_carriers;
    u16 element_mask;
    u8 level;
    bool is_alive;
    bool is_capturable;    // pode ser capturada quando vida < 30%
    CreatureState state;
} Creature;

void creature_init(Creature* c, Vector2 pos, u16 element, u8 level);
void creature_update(Creature* c, Vector2 player_pos, Vector2 veredim_pos, f32 dt);
void creature_draw(const Creature* c);

#endif // GAME_ENTITIES_CREATURE_H