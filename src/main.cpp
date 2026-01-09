#include "raylib.h"
#include "game/game.h"

int main(void) {
    InitWindow(1280, 720, "Veredins");
    SetTargetFPS(60);

    Game game = {
        .is_running = true,
        .time = 0.0f
    };
    game_init(&game);

    while (!WindowShouldClose() && game.is_running) {
        f32 dt = GetFrameTime();
        game_update(&game, dt);

        BeginDrawing();
        ClearBackground(WHITE);
        game_render(&game);
        EndDrawing();
    }
    game_shutdown(&game);
    CloseWindow();
    
    return 0;
}