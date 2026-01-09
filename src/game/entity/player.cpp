#include <math.h>

#include "game/entity/player.h"
#include "raylib.h"

void player_init(Player* p, f32 x, f32 y) {
    p->id = 0; // 0 como um ID padrão
    p->x = x;
    p->y = y;
    p->speed = 200.0f; 
    p->health = 100;
    p->max_health = 100;
    p->is_online = true;
}

void player_update(Player* p, f32 dt, f32 dir_x, f32 dir_y) {
    // Normaliza a direção
    f32 length = sqrtf(dir_x * dir_x + dir_y * dir_y);
    if (length != 0) {
        dir_x /= length;
        dir_y /= length;
    }

    // Atualiza a posição do jogador
    p->x += dir_x * p->speed * dt;
    p->y += dir_y * p->speed * dt;
}

void player_draw(const Player* p) {
    DrawCircleV(
        (Vector2){
            p->x, p->y
        },
        20,
        BLUE
    );
    DrawText(
        TextFormat("HP: %d/%d", p->health, p->max_health), 
        (int)p->x - 30, 
        (int)p->y - 40,
        10,
        WHITE
    );
}