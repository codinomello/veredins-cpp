#include <cmath>

#include "veredim.h"
#include "raymath.h"

void veredim_init(Veredim* v, f32 x, f32 y, u16 element_mask) {
    *v = {
        .pos = { x, y },
        .vel = { 0, 0 },
        .dir = { 0, 0 },
        .radius = 5.5f,
        .orbit_speed = 1.0f,
        .orbit_radius = 65.0f,
        .health = 60, 
        .max_health = 60,
        .attack = 12,
        .count = INITIAL_VEREDIM_COUNT,
        .element_mask = element_mask,
        .state = VEREDIM_FOLLOW,
        .is_alive = true
    };
}

void veredim_update(Veredim* v, Player* p, Creature* c, u32 index, f32 dt) {
    if (!v->is_alive) return;
    switch (v->state) {
        case VEREDIM_FOLLOW: {
            f32 angle_step = (2.0f * PI) / (f32)v->count;
            f32 current_angle = (f32)GetTime() * v->orbit_speed + (index * angle_step);

            // 2. definicao da distancia (camadas por elemento)
            f32 dist = v->orbit_radius;
            if (v->element_mask & ELEMENT_FIRE)  dist -= 20.0f; // camada interna
            if (v->element_mask & ELEMENT_PLANT) dist += 20.0f; // camada externa

            // 3. calculo da posicao alvo ao redor do player
            Vector2 target = {
                p->pos.x + cosf(current_angle) * dist,
                p->pos.y + sinf(current_angle) * dist
            };

            // 4. interpolacao suave (lerp) para movimento fluido
            v->pos = Vector2Lerp(v->pos, target, 10.0f * dt);
            } break;
        case VEREDIM_ATTACK: {
            // move-se em direção à criatura alvo
            v->pos = Vector2MoveTowards(v->pos, c->pos, 150.0f * dt);
            
            // lógica de dano e verificação de fraqueza elemental
            f32 dmg = (f32)v->attack * dt;
            if (veredim_element_is_strong(v->element_mask, c->element_mask)) dmg *= 2.0f;
            c->health -= (int)dmg;

            if (c->health <= 0) v->state = VEREDIM_RETURN;
        } break;

        case VEREDIM_THROWN: {
            // move-se usando a velocidade definida no momento do clique
            v->pos = Vector2Add(v->pos, Vector2Scale(v->vel, dt));

            // retorna se o veredim se afastar demais do jogador
            if (Vector2Distance(v->pos, p->pos) > 600.0f) {
                v->state = VEREDIM_RETURN;
            }
        } break;

        case VEREDIM_RETURN: {
            // volta rapidamente para o jogador para retomar a órbita
            v->pos = Vector2MoveTowards(v->pos, p->pos, 250.0f * dt);
            
            if (Vector2Distance(v->pos, p->pos) < 20.0f) {
                v->state = VEREDIM_FOLLOW;
            }
        } break;
    }
}

void veredim_draw(const Veredim* v) {
    if (!v->is_alive) return;

    Color color = entity_get_color(v->element_mask);
    
    // efeito visual de pulso e desenho do corpo
    f32 pulse = std::sin((f32)GetTime() * 3.0f) * 2.0f;
    DrawCircleLinesV(v->pos, v->radius + 6.0f + pulse, ColorAlpha(color, 0.6f));
    DrawCircleV(v->pos, v->radius, color);
    
    // barra de vida simplificada acima do veredim
    f32 hp_pct = (f32)v->health / v->max_health;
    DrawRectangle(v->pos.x - 15, v->pos.y - 15, 30, 3, BLACK);
    DrawRectangle(v->pos.x - 15, v->pos.y - 15, (int)(30 * hp_pct), 3, LIME);
}

bool veredim_element_is_strong(u32 a, u32 b) {
    // tabela de forças: fogo > planta > água > fogo
    if ((a & ELEMENT_FIRE)  && (b & ELEMENT_PLANT)) return true;
    if ((a & ELEMENT_WATER) && (b & ELEMENT_FIRE))  return true;
    if ((a & ELEMENT_PLANT) && (b & ELEMENT_WATER)) return true;
    return false;
}