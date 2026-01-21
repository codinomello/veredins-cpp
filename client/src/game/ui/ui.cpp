#include "game/core/constants.h"
#include "game/elements/element.h"
#include "ui.h"

void ui_init(Ui* ui) {
    *ui = {
        .font = GetFontDefault(), // helvetica = (LoadFontEx(FONT_PATH, UI_FONT_SIZE, nullptr, 0))
        .score = 0,
        .veredim_count = INITIAL_VEREDIM_COUNT,
        .selected_element = ELEMENT_FIRE

    };
    // configura o filtro da fonte para não ficar borrada ao redimensionar
    // SetTextureFilter(ui->font.texture, TEXTURE_FILTER_BILINEAR);
}

void ui_update(Ui* ui, f32 dt) {
    // placeholder para animações de ui futuras
}

void ui_draw(const Ui* ui, i32 player_health, i32 player_max_health, 
             i32 wave, f32 game_time, bool game_over) {
    // painel superior
    DrawRectangle(0, 0, WINDOW_WIDTH, 60, ColorAlpha(BLACK, 0.7f));
    
    // coluna esquerda
    DrawTextEx(ui->font, TextFormat("SCORE: %d", ui->score), Vector2{20, 15}, 20, 2, YELLOW);
    DrawTextEx(ui->font, TextFormat("WAVE: %d", wave), Vector2{20, 35}, 16, 2, RAYWHITE);
    
    // coluna meio
    DrawTextEx(ui->font, TextFormat("VEREDINS: %d/%d", ui->veredim_count, MAX_VEREDIM_COUNT), 
               Vector2{200, 15}, 20, 2, LIME);
    DrawTextEx(ui->font, TextFormat("TIME: %.0fs", game_time), 
               Vector2{200, 35}, 16, 2, LIGHTGRAY);
    
    // coluna direita - vida do player
    f32 hp_ratio = (f32)player_health / (f32)(player_max_health);
    DrawRectangle(WINDOW_WIDTH - 220, 20, 200, 25, ColorAlpha(BLACK, 0.8f));
    DrawRectangle(WINDOW_WIDTH - 218, 22, (i32)(196 * hp_ratio), 21, 
                  hp_ratio > 0.3f ? GREEN : RED);
    DrawTextEx(ui->font, TextFormat("HP: %d/%d", player_health, player_max_health), 
               Vector2{(f32)(WINDOW_WIDTH - 210), 25}, 16, 2, WHITE);
    
    // indicador de tipo selecionado
    DrawRectangle(WINDOW_WIDTH - 120, 70, 100, 40, ColorAlpha(BLACK, 0.7f));
    DrawText("TIPO:", WINDOW_WIDTH - 115, 75, 12, GRAY);
    DrawCircleV(Vector2{(f32)WINDOW_WIDTH - 60, 90}, 12, 
                element_get_color(ui->selected_element));
    
    // controles
    DrawRectangle(0, WINDOW_HEIGHT - 35, WINDOW_WIDTH, 35, ColorAlpha(BLACK, 0.7f));
    DrawText("WASD: Mover | SPACE: Whistle | CLICK: Arremessar | TAB: Trocar Tipo", 
             10, WINDOW_HEIGHT - 25, 14, LIGHTGRAY);
    
    // game over
    if (game_over) {
        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, ColorAlpha(BLACK, 0.8f));
        DrawText("GAME OVER", WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT/2 - 80, 60, RED);
        DrawText(TextFormat("SCORE FINAL: %d", ui->score), 
                 WINDOW_WIDTH/2 - 120, WINDOW_HEIGHT/2, 30, YELLOW);
        DrawText(TextFormat("WAVES: %d", wave), 
                 WINDOW_WIDTH/2 - 80, WINDOW_HEIGHT/2 + 40, 24, WHITE);
        DrawText("Pressione ESC para sair", WINDOW_WIDTH/2 - 110, 
                 WINDOW_HEIGHT/2 + 90, 20, GRAY);
    }
}