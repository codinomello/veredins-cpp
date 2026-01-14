#include "game/core/constants.h"
#include "camera.h"

#include "raymath.h"

void camera_init(GameCamera* cam, Vector2 start_pos) {
    // configura a câmera interna
    *cam = {
        .rl {
            .offset = (Vector2){ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f },
            .target = start_pos,
            .rotation = 0.0f,
            .zoom = 1.0f
        },
        .smooth = 5.0f
    };
}

void camera_update(GameCamera* cam, Vector2 player_pos, Vector2 player_look, f32 dt) {
    // alvo: um ponto entre o player e o mouse (30% em direção ao mouse
    Vector2 look_dir = Vector2Scale(player_look, 40.0f);
    Vector2 look_target = Vector2Add(player_pos, look_dir);

    // lerp: move o target da câmera suavemente em direção ao alvo
    cam->rl.target = Vector2Lerp(cam->rl.target, look_target, cam->smooth * dt);
    
    // mantém o offset atualizado (caso a janela mude de tamanho)
    cam->rl.offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
}