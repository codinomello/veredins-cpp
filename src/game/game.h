#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <vector>
#include <memory>

#include "game/core/camera.h"
#include "entities/creature.h"
#include "entities/veredim.h"
#include "entities/player.h"
#include "input/input.h"
#include "world/map.h"
#include "ui/ui.h"

typedef struct Game {
    std::vector<std::unique_ptr<Veredim>> veredins;
    std::vector<std::unique_ptr<Creature>> creatures;
    Player player;
    Map map;
    GameCamera game_camera;
    Camera2D rl_camera;
    Input input;
    Ui ui;
    f32  elapsed_time;
    bool is_running;
} Game;

void game_init(Game* g);
void game_update(Game* g, f32 dt);
void game_render(Game* g);
void game_shutdown(Game* g);

#endif // GAME_GAME_H