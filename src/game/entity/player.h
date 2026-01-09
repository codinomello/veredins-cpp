#ifndef GAME_ENTITY_PLAYER_H
#define GAME_ENTITY_PLAYER_H

#include "game/core/types.h"

typedef struct Player {
    u32 id;

    f32 x;
    f32 y;
    f32 speed;

    i32 health;
    i32 max_health;

    bool is_online;
} Player;

void player_init(Player* player, f32 x, f32 y);
void player_update(Player* player, f32 dt, f32 dir_x, f32 dir_y);
void player_draw(const Player* player);
void player_take_damage(Player* player, f32 damage);

#endif // GAME_ENTITY_PLAYER_H