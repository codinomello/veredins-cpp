#ifndef GAME_ENTITY_VEREDIM_H
#define GAME_ENTITY_VEREDIM_H

#include "game/core/types.h"
#include "entity.h"
#include "player.h"
#include "creature.h"

typedef enum VeredimState : u8 {
    VEREDIM_IDLE,
    VEREDIM_FOLLOW,
    VEREDIM_THROWN,
    VEREDIM_ATTACK,
    VEREDIM_CAPTURE,
    VEREDIM_RETURN
} VeredimState;

typedef struct Veredim {
    Vector2 pos;
    Vector2 vel;
    f32 radius;
    f32 orbit_angle;
    f32 state_timer;
    i32 health;
    i32 max_health;
    i32 attack;
    i32 carry_target_id;
    u32 xp;              // experiência para evolução
    u32 count;           // quantidade de veredins ativos
    u16 element_mask;    // elemento do veredim (bit mask)
    u8 level;            // sistema de level pokémon-style
    u8 layer;            // camada de órbita (0=interna, 1=média, 2=externa)
    u8 evolution_stage;  // 0=básico, 1=médio, 2=final
    bool is_alive;
    bool is_carrying;
    VeredimState state;
} Veredim;

void veredim_init(Veredim* v, f32 x, f32 y, u16 element_mask);
void veredim_update(Veredim* v, Player* p, u32 total_count, u32 index, f32 dt);
void veredim_draw(const Veredim* v, f32 game_time);
void veredim_check_evolution(Veredim* v);
void veredim_give_xp(Veredim* v, i32 amount);

#endif // GAME_ENTITY_VEREDIM_H