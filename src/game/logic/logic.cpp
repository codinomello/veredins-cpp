#include "logic.h"
#include "game/game.h"
#include "game/core/constants.h"
#include "raymath.h"
#include <cstdlib>

void logic_check_map_collision(Vector2* pos, f32 radius, const Map* map) {
    // TILE_SIZE costuma ser 32 ou 64, certifique-se que está no constants.h ou use um valor fixo
    const f32 T_SIZE = 64.0f; 

    u32 start_x = (u32)fmaxf(0, (pos->x - radius) / T_SIZE);
    u32 end_x   = (u32)fminf(map->width - 1, (pos->x + radius) / T_SIZE);
    u32 start_y = (u32)fmaxf(0, (pos->y - radius) / T_SIZE);
    u32 end_y   = (u32)fminf(map->height - 1, (pos->y + radius) / T_SIZE);
    
    for (u32 y = start_y; y <= end_y; y++) {
        for (u32 x = start_x; x <= end_x; x++) {
            if (map_is_solid(map, (i32)x, (i32)y)) {
                Rectangle tile_rect = { (f32)x * T_SIZE, (f32)y * T_SIZE, T_SIZE, T_SIZE };
                
                Vector2 closest = {
                    Clamp(pos->x, tile_rect.x, tile_rect.x + tile_rect.width),
                    Clamp(pos->y, tile_rect.y, tile_rect.y + tile_rect.height)
                };
                
                Vector2 dist_vec = Vector2Subtract(*pos, closest);
                f32 distance = Vector2Length(dist_vec);
                
                if (distance < radius && distance > 0.001f) {
                    f32 overlap = radius - distance;
                    Vector2 normal = Vector2Scale(dist_vec, 1.0f / distance);
                    *pos = Vector2Add(*pos, Vector2Scale(normal, overlap));
                }
            }
        }
    }
}

void logic_spawn_creatures(Game* g, u32 count) {
    for (u32 i = 0; i < count; i++) {
        auto c = std::make_unique<Creature>();
        
        Vector2 spawn_pos;
        do {
            spawn_pos = Vector2{ (f32)(rand() % 2000), (f32)(rand() % 2000) };
        } while (Vector2Distance(spawn_pos, g->player.pos) < 300.0f);
        
        // Sincronizado com entity.h
        u16 elements[] = { ELEMENT_FIRE, ELEMENT_WATER, ELEMENT_PLANT, ELEMENT_LIGHT };
        u16 element = elements[rand() % 4];
        u8 level = 1 + (u8)(g->wave / 2);
        
        creature_init(c.get(), spawn_pos.x, spawn_pos.y, element, level);
        g->creatures.push_back(std::move(c));
    }
}

void logic_spawn_objects(Game* g, u32 count) {
    for (u32 i = 0; i < count; i++) {
        auto obj = std::make_unique<Object>();
        ObjectType type = (ObjectType)(rand() % 4);
        Vector2 spawn_pos = { (f32)(rand() % 2000), (f32)(rand() % 2000) };
        
        object_init(obj.get(), spawn_pos.x, spawn_pos.y, type);
        g->objects.push_back(std::move(obj));
    }
}

void logic_check_veredim_evolution(Veredim* v) {
    u32 xp_needed = (v->evolution_stage + 1) * 100;
    if (v->xp >= xp_needed && v->evolution_stage < 2) {
        v->evolution_stage++;
        v->xp = 0;
        v->max_health += 30;
        v->health = v->max_health;
        v->attack += 5;
        v->radius += 1.0f;
    }
}

Color logic_get_element_color(u16 element) {
    if (element & ELEMENT_FIRE)     return RED;
    if (element & ELEMENT_WATER)    return BLUE;
    if (element & ELEMENT_PLANT)    return GREEN;
    if (element & ELEMENT_ELECTRIC) return YELLOW;
    if (element & ELEMENT_EARTH)    return BROWN;
    if (element & ELEMENT_ICE)      return SKYBLUE;
    if (element & ELEMENT_POISON)   return PURPLE;
    if (element & ELEMENT_LIGHT)    return GOLD;
    return GRAY;
}

f32 logic_type_effectiveness(u16 attacker, u16 defender) {
    if ((attacker & ELEMENT_FIRE) && (defender & ELEMENT_PLANT)) return 2.0f;
    if ((attacker & ELEMENT_WATER) && (defender & ELEMENT_FIRE)) return 2.0f;
    if ((attacker & ELEMENT_PLANT) && (defender & ELEMENT_WATER)) return 2.0f;
    
    if ((attacker & ELEMENT_FIRE) && (defender & ELEMENT_WATER)) return 0.5f;
    if ((attacker & ELEMENT_WATER) && (defender & ELEMENT_PLANT)) return 0.5f;
    if ((attacker & ELEMENT_PLANT) && (defender & ELEMENT_FIRE)) return 0.5f;
    
    return 1.0f;
}