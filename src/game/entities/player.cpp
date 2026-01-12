#include <cmath>

#include "player.h"
#include "raymath.h"

void player_init(Player* p, f32 x, f32 y) {
    *p = {
        .pos = { x, y },
        .radius = 10.0f,
        .speed = 200.0f,
        .health = 100,
        .max_health = 100,
        .id = 0,
        .is_alive = true,
        .is_online = true
    };
}

void player_update(Player* p, const Map* map, Input* input, f32 dt) {
    if (!p->is_alive) return;

    p->pos.x += input->move.x * p->speed * dt;
    p->pos.y += input->move.y * p->speed * dt;
}

void player_draw(const Player* p) {
    // 1. definições de estilo (minimalista)
    const Color main_color = RAYWHITE;
    const f32 time = (f32)GetTime();
    const f32 pulse = sinf(time * 2.5f) * 2.0f;
    const f32 radius = 18.0f;

    // 2. anel de energia (substitui a aura e a sombra)
    // um único anel que pulsa suavemente indicando a presença do player
    DrawCircleLinesV(p->pos, radius + 4.0f + pulse, ColorAlpha(main_color, 0.5f));

    // 3. corpo (estilo flat design)
    // usamos uma cor levemente mais escura para o fundo para dar profundidade sem usar preto
    DrawCircleV(p->pos, radius, ColorBrightness(main_color, -0.2f)); 
    DrawCircleV(p->pos, radius - 2.0f, main_color);
    
    // detalhe único: um ponto direcional simples em vez de brilho genérico
    // ajuda a saber para onde o player está olhando (p->dir)
    Vector2 pointer = Vector2Add(p->pos, Vector2Scale(p->dir, 8.0f));
    DrawCircleV(pointer, 3.0f, WHITE);

    // 4. barra de vida integrada (sem bordas, apenas uma linha)
    f32 hp_ratio = (f32)p->health / p->max_health;
    f32 bar_w = 40.0f;
    
    // desenha apenas a linha de fundo e a linha de vida (mais fino e elegante)
    Vector2 line_start = { p->pos.x - bar_w/2, p->pos.y - 30.0f };
    DrawRectangleV(line_start, { bar_w, 2.0f }, ColorAlpha(WHITE, 0.2f));
    DrawRectangleV(line_start, { bar_w * hp_ratio, 2.0f }, (hp_ratio > 0.3f) ? WHITE : RED);

    // 5. texto minimalista (apenas o número, sem o "max")
    DrawText(TextFormat("%d", p->health), (int)p->pos.x + 22, (int)p->pos.y - 34, 10, ColorAlpha(WHITE, 0.8f));
}