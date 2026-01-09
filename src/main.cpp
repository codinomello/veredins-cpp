#include "game/game.h"
#include "raylib.h"

constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

int main(void) {
    Game game = {
        .is_running = true,
        .title = "Veredins",
        .background_color = LIGHTGRAY,
        .time = GetTime()
    };

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, game.title.c_str());
    SetTargetFPS(60);

    game_init(&game);
    while (!WindowShouldClose() && game.is_running) {
        f32 dt = GetFrameTime();
        game_update(&game, dt);

        BeginDrawing();
        ClearBackground(game.background_color);
        game_render(&game);
        EndDrawing();
    }
    game_shutdown(&game);
    CloseWindow();
    
    return 0;
}