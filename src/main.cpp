#include <memory>

#include "game/game.h"

int main(void) {
    // cria o jogo
    std::unique_ptr<Game> game = std::make_unique<Game>();

    // inicializa lógica do jogo
    game_init(game.get());

    while (!WindowShouldClose() && game->is_running) {
        // delta time
        f32 dt = GetFrameTime();

        // atualiza lógica
        game_update(game.get(), dt);

        BeginDrawing();
        ClearBackground(game->background_color);

        BeginMode2D(game->rl_camera);

        // render do mundo
        game_render(game.get());

        EndMode2D();

        // ui fora da camera
        game_render_ui(game.get());

        EndDrawing();
    }

    // shutdown ordenado
    game_shutdown(game.get());

    CloseWindow();

    return 0;
}