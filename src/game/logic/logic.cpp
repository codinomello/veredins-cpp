#include "logic.h"
#include "raymath.h"

void logic_check_map_collision(Vector2* pos, f32 radius, const Map* map) {
    // localiza os tiles ao redor do objeto (otimização por "broadphase")
    int start_x = (int)(pos->x - radius) / TILE_SIZE;
    int end_x   = (int)(pos->x + radius) / TILE_SIZE;
    int start_y = (int)(pos->y - radius) / TILE_SIZE;
    int end_y   = (int)(pos->y + radius) / TILE_SIZE;
    
    for (int y = start_y; y <= end_y; y++) {
        for (int x = start_x; x <= end_x; x++) {
            // verifica se o tile é sólido (ex.: pedra ou água)
            if (map_is_solid(map, x, y)) {
                Rectangle tile_rect = { (f32)x * TILE_SIZE, (f32)y * TILE_SIZE, (f32)TILE_SIZE, (f32)TILE_SIZE };
                
                Vector2 closest = {
                    Clamp(pos->x, tile_rect.x, tile_rect.x + tile_rect.width),
                    Clamp(pos->y, tile_rect.y, tile_rect.y + tile_rect.height)
                };
                
                Vector2 dist_vec = Vector2Subtract(*pos, closest);
                f32 distance = Vector2Length(dist_vec);
                
                if (distance < radius && distance > 0.0f) {
                    f32 overlap = radius - distance;
                    Vector2 normal = Vector2Scale(dist_vec, 1.0f / distance);
                    *pos = Vector2Add(*pos, Vector2Scale(normal, overlap));
                }
            }
        }
    }
}