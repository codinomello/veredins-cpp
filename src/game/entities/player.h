#ifndef GAME_ENTITY_PLAYER_H
#define GAME_ENTITY_PLAYER_H

#include "game/core/types.h"
#include "game/world/map.h"
#include "game/input/input.h"
#include "raylib.h"

typedef struct Player {
    Vector2 position;
    Vector2 direction;
    Vector2 velocity;
    Vector2 look;
    struct {
        f32 width;
        f32 height;
    } size;
    f32 radius;
    f32 speed;
    i32 health;
    i32 max_health;
    u32 id;
    bool is_alive;
    bool is_online;
} Player;

void player_init(Player* p, f32 x, f32 y, f32 width, f32 height);
void player_update(Player* p, const Map* map, Input input, f32 dt);
void player_draw(const Player* p);
void player_take_damage(Player* p, f32 damage);
void player_move_x(Player* p, const Map* map);
void player_move_y(Player* p, const Map* map);

#endif // GAME_ENTITY_PLAYER_H