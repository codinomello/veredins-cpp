#ifndef GAME_ENTITY_PLAYER_H
#define GAME_ENTITY_PLAYER_H

#include "../core/types.h"
#include "raylib.h"

typedef struct Player {
    u32 id;
    Vector2 pos;
    struct Size {
        f32 width;
        f32 height;
    } size;
    f32 speed;
    i32 health;
    i32 max_health;
    bool is_online;
} Player;

void player_init(Player* player, f32 x, f32 y, f32 width, f32 height);
void player_update(Player* player, f32 dt, f32 dx, f32 dy);
void player_draw(const Player* player);
void player_take_damage(Player* player, f32 damage);

#endif // GAME_ENTITY_PLAYER_H