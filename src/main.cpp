#include "game/game.h"
#include "raylib.h"

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

int main(void) {
    Game game;
    game_init(&game);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, game.title.c_str());
    SetTargetFPS(60);


    while (!WindowShouldClose() && game.is_running) {
        f32 dt = GetFrameTime();
        game_update(&game, dt);

        BeginDrawing();
        ClearBackground(game.background_color);
        BeginMode2D(game.rl_camera);

        game_render(&game);
        
        EndMode2D();

        // Render UI - estático
        game_render_ui(&game);

        EndDrawing();
    }
    game_shutdown(&game);

    CloseWindow();
    
    return 0;
}