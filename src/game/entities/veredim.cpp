#include <cmath>

#include "../entities/veredim.h"
#include "../core/math.h"
#include "raylib.h"

Veredim veredim_init(Veredim* v, f32 x, f32 y, u32 element) {
    return (Veredim) {
        v->id = 0,
        v->pos = {
            x, y
        },
        v->target_pos = {
            x, y
        },
        v->health = 60,
        v->max_health = 60,
        v->element = element,
        v->attack = 12,
        v->defense = 8,
        v->radius = 8.0f,
        v->orbit_speed = 1.0f,
        v->state = VEREDIM_FOLLOWING
    };

    // Veredim() : id(0), pos{0,0}, target_pos{0,0}, health(60), max_health(60),
    //     element(ELEMENT_NONE), attack(12), defense(8), radius(8.0f),
    //     angle(0.0f), orbit_radius(50.0f), orbit_speed(1.0f), state(VEREDIM_FOLLOWING) {};
}

void veredim_update(Veredim* v, f32 dt, f32 player_x, f32 player_y, u32 index) {
    if (v->state != VEREDIM_FOLLOWING) return;

    f32 t = (f32)GetTime() + (index * 0.5f);
    f32 target_x = player_x + cosf(t) * 90.0f; 
    f32 target_y = player_y + sinf(t) * 90.0f;

    // 2. Segue o alvo suavemente
    v->pos.x = lerp(v->pos.x, target_x, 6.0f * dt);
    v->pos.y = lerp(v->pos.y, target_y, 6.0f * dt);
}

Color veredim_get_color(u32 element) {
    switch (element) {
    case ELEMENT_FIRE:
        return RED;
    case ELEMENT_WATER:
        return BLUE;
    case ELEMENT_PLANT:
        return GREEN;
    case ELEMENT_ELECTRIC:
        return YELLOW;
    case ELEMENT_EARTH:
        return BROWN;
    case ELEMENT_ICE:
        return SKYBLUE;
    default:
        return GRAY;
        break;
    }
}

void veredim_draw(const Veredim* v) {
    // 1. Cores e Variáveis de Efeito
    Color base_color = veredim_get_color(v->element);
    
    // Efeito de pulso para a aura usando o tempo global
    float time = (float)GetTime();
    float pulse = sinf(time * 3.0f + (v->pos.x * 0.1f)) * 2.0f; 
    
    // 2. Desenhar a Aura (O "Circle" que você pediu)
    // Desenhamos um círculo vazado com a cor do elemento levemente transparente
    Color aura_color = ColorAlpha(base_color, 0.6f);
    DrawCircleLinesV(v->pos, v->radius + 6.0f + pulse, aura_color);
    
    // 3. Desenhar o Corpo do Veredim
    // Desenha uma bordinha escura para dar profundidade
    DrawCircleV(v->pos, v->radius + 1.0f, BLACK); 
    DrawCircleV(v->pos, v->radius, base_color);
    
    // Adiciona um pequeno brilho no "olho" ou topo para parecer 3D
    DrawCircleV({v->pos.x - 2, v->pos.y - 2}, v->radius * 0.3f, ColorAlpha(WHITE, 0.5f));

    // 4. Barra de Vida Visual (Mais bonita que apenas texto)
    float health_bar_width = 30.0f;
    float health_percent = (float)v->health / (float)v->max_health;
    Vector2 bar_pos = { v->pos.x - health_bar_width/2.0f, v->pos.y - v->radius - 15.0f };

    // Fundo da barra (Preto)
    DrawRectangleV(bar_pos, {health_bar_width, 4}, ColorAlpha(BLACK, 0.8f));
    // Vida atual (Verde ou cor do elemento)
    DrawRectangleV(bar_pos, {health_bar_width * health_percent, 4}, LIME);

    // Texto de HP bem pequeno e centralizado (opcional, já que a barra resolve)
    DrawText(
        TextFormat("%d/%d", v->health, v->max_health),
        (int)v->pos.x - 12,
        (int)v->pos.y - v->radius - 26,
        10,
        WHITE
    );
}