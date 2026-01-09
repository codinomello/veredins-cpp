#include "raylib.h"
#include "game/game.h"

int main(void) {
    InitWindow(1280, 720, "Veredins");
    SetTargetFPS(60);

    Game game = {};
    game_init(&game);

    while (!WindowShouldClose() && game.running) {
        f32 dt = GetFrameTime();
        game_update(&game, dt);

        BeginDrawing();
        ClearBackground(BLACK);
        game_render(&game);
        EndDrawing();
    }

    game_shutdown(&game);
    CloseWindow();
    return 0;
}