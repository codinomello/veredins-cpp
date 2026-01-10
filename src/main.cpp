#include "game/game.h"
#include "raylib.h"

Game game;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

int main(void) {
    // inicializa o jogo
    game_init(&game);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, game.title.c_str());
    SetTargetFPS(60);

    while (!WindowShouldClose() && game.is_running) {
        // delta time
        f32 dt = GetFrameTime();

        // atualiza o jogo
        game_update(&game, dt);

        BeginDrawing();
        ClearBackground(game.background_color);
        BeginMode2D(game.rl_camera);

        // renderiza o jogo
        game_render(&game);
        
        EndMode2D();

        // renderiza interface gráfica estática
        game_render_ui(&game);

        EndDrawing();
    }
    // finaliza o jogo
    game_shutdown(&game);

    CloseWindow();
    
    return 0;
}