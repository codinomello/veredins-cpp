#include <cmath>

#include "../core/math.h"
#include "../world/map.h"
#include "../world/tile.h"
#include "../logic/collision.h"
#include "../input/input.h"
#include "player.h"
#include "raylib.h"

void player_init(Player* p, f32 x, f32 y, f32 width, f32 height) {
    *p = (Player) {
        .position = {
            x, y
        },
        .direction = {
            1.0f, 1.0f
        },
        .velocity = {
            0.0f, 0.0f
        },
        .look = {
            0.0f, 0.0f
        },
        .size = {
            width, height
        },
        .speed       = 200.0f,
        .health      = 100,
        .max_health  = 100,
        .id          = 0,
        .is_alive    = true,
        .is_online   = true,
    };
}

void player_update(Player* p, const TileMap* map, Input input, f32 dt) {
    f32 speed = 200.0f;
    p->direction.x = input.x * speed * dt;
    p->direction.y = input.y * speed * dt;

    player_move_x(p, map);
    player_move_y(p, map);
}

void player_draw(const Player* p) {
    Color player_color = BLUE;
    Color aura_color = SKYBLUE;
    
    f32 time = (f32)GetTime();
    f32 pulse = sinf(time * 2.0f) * 3.0f; 
    
    DrawCircleLinesV(p->position, 20.0f + 8.0f + pulse, ColorAlpha(aura_color, 0.4f));
    DrawCircleLinesV(p->position, 20.0f + 6.0f + (pulse * 0.5f), ColorAlpha(WHITE, 0.3f));
    
    DrawEllipse((u32)p->position.x, (u32)p->position.y + 18, 15.0f, 6.0f, ColorAlpha(BLACK, 0.3f));
    
    DrawCircleV(p->position, 21.0f, BLACK);
    DrawCircleV(p->position, 20.0f, player_color);
    
    DrawCircleV({p->position.x - 4, p->position.y - 4}, 6.0f, ColorAlpha(WHITE, 0.4f));

    f32 bar_width = 50.0f;
    f32 bar_height = 6.0f;
    f32 hp_ratio = (f32)p->health / (f32)p->max_health;
    Vector2 bar_position = { p->position.x - bar_width/2.0f, p->position.y - 35.0f };

    DrawRectangleV(bar_position, {bar_width, bar_height}, ColorAlpha(BLACK, 0.8f));
    Color hp_color = (hp_ratio > 0.3f) ? LIME : RED;
    DrawRectangleV(bar_position, {bar_width * hp_ratio, bar_height}, hp_color);
    
    DrawRectangleLinesEx({bar_position.x, bar_position.y, bar_width, bar_height}, 1, ColorAlpha(WHITE, 0.5f));

    const char* hp_text = TextFormat("%d / %d", p->health, p->max_health);
    u32 text_width = MeasureText(hp_text, 12);
    DrawText(hp_text, (u32)p->position.x - text_width/2, (u32)p->position.y - 50, 12, WHITE);
}

void player_move_x(Player* p, const TileMap* map) {
    p->position.x += p->direction.x;

    i32 left   = (i32)(p->position.x) / TILE_SIZE;
    i32 right  = (i32)(p->position.x + p->size.width) / TILE_SIZE;
    i32 top    = (i32)(p->position.y) / TILE_SIZE;
    i32 bottom = (i32)(p->position.y + p->size.height) / TILE_SIZE;

    for (i32 y = top; y <= bottom; y++) {
        for (i32 x = left; x <= right; x++) {
            TileType t = map->tiles[y][x];
            if (!tile_is_solid(t)) continue;

            f32 tx = x * TILE_SIZE;
            f32 ty = y * TILE_SIZE;

            if (aabb_intersect(p->position.x, p->position.y, p->size.width, p->size.height,
                               tx, ty, TILE_SIZE, TILE_SIZE)) {
                if (p->direction.x > 0)
                    p->position.x = tx - p->size.width;
                else if (p->direction.x < 0)
                    p->position.x = tx + TILE_SIZE;
            }
        }
    }
}

void player_move_y(Player* p, const TileMap* map) {
    p->position.y += p->direction.y;

    i32 left   = (i32)(p->position.x) / TILE_SIZE;
    i32 right  = (i32)(p->position.x + p->size.width) / TILE_SIZE;
    i32 top    = (i32)(p->position.y) / TILE_SIZE;
    i32 bottom = (i32)(p->position.y + p->size.height) / TILE_SIZE;

    for (i32 y = top; y <= bottom; y++) {
        for (i32 x = left; x <= right; x++) {
            TileType t = map->tiles[y][x];
            if (!tile_is_solid(t)) continue;

            f32 tx = x * TILE_SIZE;
            f32 ty = y * TILE_SIZE;

            if (aabb_intersect(p->position.x, p->position.y, p->size.width, p->size.height,
                               tx, ty, TILE_SIZE, TILE_SIZE)) {
                if (p->direction.y > 0)
                    p->position.y = ty - p->size.height;
                else if (p->direction.y < 0)
                    p->position.y = ty + TILE_SIZE;
            }
        }
    }
}