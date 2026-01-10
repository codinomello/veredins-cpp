#ifndef GAME_ENTITY_VEREDIM_H
#define GAME_ENTITY_VEREDIM_H

#include "../element/element.h"
#include "../core/types.h"
#include "player.h"
#include "creature.h"
#include "raylib.h"

typedef enum VeredimState {
    VEREDIM_IDLE = 0,
    VEREDIM_FOLLOW,
    VEREDIM_THROWN,
    VEREDIM_ATTACK,
    VEREDIM_RETURN,
    VEREDIM_CARRY,
    VEREDIM_STUN,
} VeredimState;

typedef struct Veredim {
    Vector2 position;
    Vector2 target;
    Vector2 velocity;
    struct {
        f32 width;
        f32 height;
    } size;
    f32 speed;
    f32 radius;
    f32 angle;
    f32 orbit_speed;
    f32 orbit_radius;
    f32 attack_cooldown;
    f32 attack_timer;
    i32 health;
    i32 max_health;
    i32 attack;
    i32 defense;
    u32 id;
    u32 element_mask;
    VeredimState state;
    bool is_alive;
} Veredim;

void veredim_init(Veredim* v, f32 x, f32 y, u32 element_mask);
void veredim_follow(Veredim* v, Player* p, u32 index, f32 dt);
void veredim_attack(Veredim* v, Creature* c, f32 dt);
void veredim_update(Veredim* v, Player* p, Creature* c, u32 index, f32 dt);
Color veredim_get_color(u32 element_mask);
void veredim_draw(const Veredim* v);
bool veredim_element_is_strong(u32 a, u32 b);

#endif // GAME_ENTITY_VEREDIM_H