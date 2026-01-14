#ifndef GAME_ENTITY_VEREDIM_H
#define GAME_ENTITY_VEREDIM_H

#include <vector>

#include "game/core/types.h"
#include "game/elements/element.h"
#include "player.h"
#include "creature.h"

typedef enum VeredimState : u8 {
    VEREDIM_IDLE,
    VEREDIM_FOLLOW,
    VEREDIM_THROWN,
    VEREDIM_ATTACK,
    VEREDIM_CARRY,
    VEREDIM_RETURN,
    VEREDIM_CAPTURED,
    VEREDIM_DECEASED
} VeredimState;

typedef struct VeredimOrbit {
    f32 radius;     // distância do jogador
    f32 angle;      // ângulo
    u32 capacity;   // máximo de veredins nesta camada
    u32 current;    // quantos já foram alocados aqui neste frame/instância
    u8 slot;        // posição do veredim na órbita
    u8 layer;       // camada de órbita (0=interna, 1=média, 2=externa)
} VeredimOrbit;

typedef struct Veredim {
    Vector2 pos;
    Vector2 vel;
    f32 radius;
    f32 capture_radius;
    f32 state_timer;
    f32 panic_timer;
    i32 health;
    i32 max_health;
    i32 attack;
    i32 carry_target_id;
    u32 xp;              // experiência para evolução
    u32 count;           // quantidade de veredins ativos
    u16 element_mask;    // elemento do veredim (bit mask)
    u8 level;            // sistema de level pokémon-style
    u8 evolution_stage;  // 0=básico, 1=médio, 2=final
    bool is_alive;
    bool is_carrying;
    std::vector<VeredimOrbit> orbits;
    VeredimState state;
    VeredimOrbit orbit;
} Veredim;

void veredim_init(Veredim* v, Vector2 pos, u16 element_mask);
void veredim_update(Veredim* v, Vector2 player_pos, f32 dt);
void veredim_draw(const Veredim* v, f32 game_time);
void veredim_check_evolution(Veredim* v);
void veredim_give_xp(Veredim* v, i32 amount);

#endif // GAME_ENTITY_VEREDIM_H