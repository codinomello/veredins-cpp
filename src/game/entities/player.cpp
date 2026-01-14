#include <cmath>

#include "player.h"

#include "raymath.h"

void player_init(Player* p, Vector2 pos) {
    *p = {
        .pos = pos,
        .radius = 10.0f,
        .speed = 200.0f,
        .health = 100,
        .max_health = 100,
        .id = 0,
        .is_alive = true,
        .is_online = true
    };
}

void player_update(Player* p, Input* input, f32 dt) {
    if (!p->is_alive) return;
    p->pos.x += input->move.x * p->speed * dt;
    p->pos.y += input->move.y * p->speed * dt;
}

void player_draw(const Player* p) {
    // definições de estilo
    const Color main_color = RAYWHITE;
    const f32 time = (f32)GetTime();
    const f32 pulse = sinf(time * 2.5f) * 2.0f;
    const f32 radius = 18.0f;

    // anel de energia
    DrawCircleLinesV(p->pos, radius + 4.0f + pulse, ColorAlpha(main_color, 0.5f));

    // corpo do player
    DrawCircleV(p->pos, radius, ColorBrightness(main_color, -0.2f)); 
    DrawCircleV(p->pos, radius - 2.0f, main_color);
    
    // barra de vida integrada (sem bordas, apenas uma linha)
    f32 hp_ratio = (f32)p->health / p->max_health;
    f32 bar_w = 40.0f;
    
    // desenha apenas a linha de fundo e a linha de vida (mais fino e elegante)
    Vector2 line_start = { p->pos.x - bar_w/2, p->pos.y - 30.0f };
    DrawRectangleV(line_start, { bar_w, 2.0f }, ColorAlpha(WHITE, 0.2f));
    DrawRectangleV(line_start, { bar_w * hp_ratio, 2.0f }, (hp_ratio > 0.3f) ? WHITE : RED);

    // texto (apenas o número, sem o "max")
    DrawText(
        TextFormat("%d", p->health),
        p->pos.x + 22,
        p->pos.y - 34,
        10, ColorAlpha(WHITE, 0.8f)
    );
}