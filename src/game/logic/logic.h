#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <memory>
#include "game/entities/entity.h"
#include "game/world/map.h"
#include "game/core/types.h"
#include "raylib.h"

// Forward declaration para evitar inclusão circular
struct Game;
struct Veredim;

void logic_check_map_collision(Vector2* pos, f32 radius, const Map* map);
f32  logic_type_effectiveness(u16 attacker, u16 defender);
void logic_spawn_creatures(Game* g, u32 count);
void logic_spawn_objects(Game* g, u32 count);
void logic_check_veredim_evolution(Veredim* v);
Color logic_get_element_color(u16 element);

#endif