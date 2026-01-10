#include <cmath>

#include "../core/math.h"
#include "player.h"
#include "raylib.h"

void player_init(Player* p, f32 x, f32 y) {
    p->id = 0; // 0 como um ID padrão
    p->pos = {
        x, y
    };
    p->speed = 200.0f; 
    p->health = 100;
    p->max_health = 100;
    p->is_online = true;
}

void player_update(Player* p, f32 dt, f32 dx, f32 dy) {
    // Normaliza a direção
    f32 len = std::sqrt(dx * dx + dy * dy);
    if (len != 0) {
        dx /= len;
        dy /= len;
    }

    // Atualiza a posição do jogador
    p->pos.x += dx * p->speed * dt;
    p->pos.y += dy * p->speed * dt;
}

void player_draw(const Player* p) {
    DrawCircleV(
        p->pos,
        20,
        BLUE
    );
    DrawText(
        TextFormat("HP: %d/%d", p->health, p->max_health), 
        (int)p->pos.x - 30, 
        (int)p->pos.y - 40,
        10,
        WHITE
    );
}