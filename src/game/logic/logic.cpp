#include <cstdlib>

#include "game/core/constants.h"
#include "game/game.h"
#include "logic.h"

#include "raymath.h"

void logic_spawn_wave(Game* g) {
    // spawna criaturas baseado na wave atual
    for (int i = 0; i < g->wave * 2; i++) {
        auto c = std::make_unique<Creature>();
        f32 rx = (f32)GetRandomValue(100, 1100);
        f32 ry = (f32)GetRandomValue(100, 600);
        creature_init(c.get(), rx, ry, ELEMENT_PLANT, (u8)g->wave);
        g->creatures.push_back(std::move(c));
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