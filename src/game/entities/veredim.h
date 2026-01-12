#ifndef GAME_ENTITY_VEREDIM_H
#define GAME_ENTITY_VEREDIM_H

#include "game/core/types.h"
#include "entity.h"
#include "player.h"
#include "creature.h"

typedef enum {
    VEREDIM_IDLE,
    VEREDIM_FOLLOW,
    VEREDIM_THROWN,
    VEREDIM_ATTACK,
    VEREDIM_RETURN,
    VEREDIM_STUN
} VeredimState;

typedef struct Veredim {
    Vector2 pos;
    Vector2 vel;
    Vector2 dir;
    f32 radius;
    f32 orbit_speed;
    f32 orbit_radius;
    i32 health, max_health;
    i32 attack;
    u16 count;
    u16 element_mask;
    VeredimState state;
    bool is_alive;
} Veredim;

void veredim_init(Veredim* v, f32 x, f32 y, u16 element_mask);
void veredim_update(Veredim* v, Player* p, Creature* c, u32 index, f32 dt);
void veredim_draw(const Veredim* v);
bool veredim_element_is_strong(u32 a, u32 b);

#endif // GAME_ENTITY_VEREDIM_H