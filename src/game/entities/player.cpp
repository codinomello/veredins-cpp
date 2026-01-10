#include <cmath>

#include "../core/math.h"
#include "../world/map.h"
#include "../world/tile.h"
#include "../logic/collision.h"
#include "player.h"
#include "raylib.h"

void player_init(Player* p, f32 x, f32 y, f32 width, f32 height) {
    p->id = 0; // 0 como um ID padrão
    p->pos = {
        x, y
    };
    p->size = {
        width, height
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
    // 1. Variáveis de estilo e efeito
    Color player_color = BLUE;
    Color aura_color = SKYBLUE;
    
    float time = (float)GetTime();
    // Aura do player pulsa um pouco mais devagar e de forma mais ampla
    float pulse = sinf(time * 2.0f) * 3.0f; 
    
    // 2. Desenhar a Aura do Player (Círculo externo)
    // Desenhamos duas linhas para dar um efeito de "grossura" ou brilho duplo
    DrawCircleLinesV(p->pos, 20.0f + 8.0f + pulse, ColorAlpha(aura_color, 0.4f));
    DrawCircleLinesV(p->pos, 20.0f + 6.0f + (pulse * 0.5f), ColorAlpha(WHITE, 0.3f));
    
    // 3. Desenhar o Corpo do Player
    // Sombra projetada no chão (opcional, mas fica muito bom)
    DrawEllipse((int)p->pos.x, (int)p->pos.y + 18, 15.0f, 6.0f, ColorAlpha(BLACK, 0.3f));
    
    // Borda e Corpo
    DrawCircleV(p->pos, 21.0f, BLACK); // Contorno
    DrawCircleV(p->pos, 20.0f, player_color);
    
    // Reflexo de luz (Glow interno)
    DrawCircleV({p->pos.x - 4, p->pos.y - 4}, 6.0f, ColorAlpha(WHITE, 0.4f));

    // 4. Barra de Vida do Player (Maior e Centralizada)
    float bar_width = 50.0f;
    float bar_height = 6.0f;
    float hp_ratio = (float)p->health / (float)p->max_health;
    Vector2 bar_pos = { p->pos.x - bar_width/2.0f, p->pos.y - 35.0f };

    // Fundo da barra
    DrawRectangleV(bar_pos, {bar_width, bar_height}, ColorAlpha(BLACK, 0.8f));
    // Vida (Cor degradê visual: fica vermelha quando baixa)
    Color hp_color = (hp_ratio > 0.3f) ? LIME : RED;
    DrawRectangleV(bar_pos, {bar_width * hp_ratio, bar_height}, hp_color);
    
    // Borda fina na barra de vida
    DrawRectangleLinesEx({bar_pos.x, bar_pos.y, bar_width, bar_height}, 1, ColorAlpha(WHITE, 0.5f));

    // Texto de HP centralizado acima da barra
    const char* hp_text = TextFormat("%d / %d", p->health, p->max_health);
    int text_width = MeasureText(hp_text, 12);
    DrawText(hp_text, (int)p->pos.x - text_width/2, (int)p->pos.y - 50, 12, WHITE);
}

static void player_move_x(Player* p, const TileMap* map, f32 dx) {
    p->pos.x += dx;

    i32 left   = (i32)(p->pos.x) / TILE_SIZE;
    i32 right  = (i32)(p->pos.x + p->size.width) / TILE_SIZE;
    i32 top    = (i32)(p->pos.y) / TILE_SIZE;
    i32 bottom = (i32)(p->pos.y + p->size.height) / TILE_SIZE;

    for (i32 y = top; y <= bottom; y++) {
        for (i32 x = left; x <= right; x++) {
            TileType t = map->tiles[y][x];
            if (!tile_is_solid(t)) continue;

            f32 tx = x * TILE_SIZE;
            f32 ty = y * TILE_SIZE;

            if (aabb_intersect(p->pos.x, p->pos.y, p->size.width, p->size.height,
                               tx, ty, TILE_SIZE, TILE_SIZE)) {
                if (dx > 0)
                    p->pos.x = tx - p->size.width;
                else if (dx < 0)
                    p->pos.x = tx + TILE_SIZE;
            }
        }
    }
}

static void player_move_y(Player* p, const TileMap* map, f32 dy) {
    p->pos.y += dy;

    i32 left   = (i32)(p->pos.x) / TILE_SIZE;
    i32 right  = (i32)(p->pos.x + p->size.width) / TILE_SIZE;
    i32 top    = (i32)(p->pos.y) / TILE_SIZE;
    i32 bottom = (i32)(p->pos.y + p->size.height) / TILE_SIZE;

    for (i32 y = top; y <= bottom; y++) {
        for (i32 x = left; x <= right; x++) {
            TileType t = map->tiles[y][x];
            if (!tile_is_solid(t)) continue;

            f32 tx = x * TILE_SIZE;
            f32 ty = y * TILE_SIZE;

            if (aabb_intersect(p->pos.x, p->pos.y, p->size.width, p->size.height,
                               tx, ty, TILE_SIZE, TILE_SIZE)) {
                if (dy > 0)
                    p->pos.y = ty - p->size.height;
                else if (dy < 0)
                    p->pos.y = ty + TILE_SIZE;
            }
        }
    }
}