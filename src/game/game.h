#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <vector>
#include <memory>

#include "game/core/camera.h"
#include "entities/creature.h"
#include "entities/veredim.h"
#include "entities/player.h"
#include "entities/object.h"
#include "input/input.h"
#include "world/map.h"
#include "ui/ui.h"

typedef struct Game {
    f32 time;
    f32 wave;
    f32 wave_timer;
    std::vector<std::unique_ptr<Veredim>> veredins;
    std::vector<std::unique_ptr<Creature>> creatures;
    std::vector<std::unique_ptr<Object>> objects;
    Player player;
    Map map;
    GameCamera camera;
    Input input;
    Ui ui;
    Image window_icon;
    Color background_color;
    bool is_running;
    bool is_game_over;
} Game;

void game_init(Game* g);
void game_update(Game* g, f32 dt);
void game_render(Game* g);
void game_shutdown(Game* g);

#endif // GAME_GAME_H