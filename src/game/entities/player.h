#ifndef GAME_ENTITY_PLAYER_H
#define GAME_ENTITY_PLAYER_H

#include "game/core/types.h"
#include "game/world/map.h"
#include "game/input/input.h"
#include "entity.h"

typedef struct Player {
    Vector2 pos;
    Vector2 dir;
    f32 radius;
    f32 speed;
    i32 health, max_health;
    u32 id;
    bool is_alive;
    bool is_online;
} Player;

void player_init(Player* p, Vector2 pos);
void player_update(Player* p, const Map* map, Input* input, f32 dt);
void player_draw(const Player* p);
void player_take_damage(Player* p, f32 damage);

#endif // GAME_ENTITY_PLAYER_H