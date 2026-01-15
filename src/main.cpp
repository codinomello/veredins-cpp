#include "game/game.h"
#include "client/client.h"

Game game;
Client client;

int main(void) {
    // incializa o jogo
    game_init(&game);
    
    // testa o cliente uma mensagem de teste ao servidor UDP
    client_test(&client);

    while (!WindowShouldClose() && game.is_running) {
        f32 dt = GetFrameTime();
        game_update(&game, dt);
        game_render(&game);
        
    }
    
    // encerra o jogo
    game_shutdown(&game);

    // encerra o cliente UDP
    client_shutdown(&client);

    return 0;
}