#include <cstdlib>

#include "game/core/constants.h"
#include "game/game.h"
#include "logic.h"

#include "raymath.h"

void logic_spawn_wave(Game* g) {
    // spawna criaturas baseado na wave atual
    for (int i = 0; i < g->wave * 2; i++) {
        auto c = std::make_unique<Creature>();
        Vector2 random = { (f32)GetRandomValue(100, 1100), (f32)GetRandomValue(100, 600) };
        creature_init(c.get(), random, ELEMENT_PLANT, (u8)g->wave);
        g->creatures.push_back(std::move(c));
    }
}


void logic_spawn_creatures(Game* g, u32 count) {
    for (u32 i = 0; i < count; i++) {
        auto c = std::make_unique<Creature>();
        
        Vector2 spawn_pos;
        do {
            spawn_pos = Vector2{
                (f32)(rand() % 1000 + 200),
                (f32)(rand() % 600 + 100)
            };
        } while (Vector2Distance(spawn_pos, g->player.pos) < 200.0f);
        
        u16 elements[] = {ELEMENT_FIRE, ELEMENT_WATER, ELEMENT_PLANT, ELEMENT_ELECTRIC, ELEMENT_EARTH, ELEMENT_ICE};
        u16 element = elements[rand() % 6];
        i32 level = 1 + (g->wave / 2);
        
        creature_init(c.get(), spawn_pos, level, element);
        g->creatures.push_back(std::move(c));
    }
}

void logic_spawn_objects(Game* g, u32 count) {
    for (u32 i = 0; i < count; i++) {
        auto obj = std::make_unique<Object>();
        ObjectType type = (ObjectType)(rand() % 4);
        Vector2 spawn_pos = {
            (f32)(rand() % 1000 + 200),
            (f32)(rand() % 600 + 100)
        };
        object_init(obj.get(), spawn_pos.x, spawn_pos.y, type);
        g->objects.push_back(std::move(obj));
    }
}