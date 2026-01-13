#include "game/core/constants.h"
#include "game/entities/entity.h"
#include "ui.h"

void ui_init(Ui* ui, Font font) {
    *ui = {
        .font = font,
        .score = 0,
        .veredim_count = INITIAL_VEREDIM_COUNT,
        .selected_element = ELEMENT_FIRE
    };
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
    f32 hp_ratio = static_cast<f32>(player_health) / static_cast<f32>(player_max_health);
    DrawRectangle(WINDOW_WIDTH - 220, 20, 200, 25, ColorAlpha(BLACK, 0.8f));
    DrawRectangle(WINDOW_WIDTH - 218, 22, static_cast<i32>(196 * hp_ratio), 21, 
                  hp_ratio > 0.3f ? GREEN : RED);
    DrawTextEx(ui->font, TextFormat("HP: %d/%d", player_health, player_max_health), 
               Vector2{static_cast<f32>(WINDOW_WIDTH - 210), 25}, 16, 2, WHITE);
    
    // indicador de tipo selecionado
    DrawRectangle(WINDOW_WIDTH - 120, 70, 100, 45, ColorAlpha(BLACK, 0.7f));
    DrawTextEx(ui->font, "TIPO:", Vector2{static_cast<f32>(WINDOW_WIDTH - 115), 75}, 12, 1, GRAY);
    
    Color elem_color = entity_get_color(ui->selected_element);
    DrawCircleV(Vector2{static_cast<f32>(WINDOW_WIDTH - 60), 95}, 12, elem_color);
    
    // tela de game over
    if (game_over) {
        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, ColorAlpha(BLACK, 0.5f));
        
        const char* dead_text = "GAME OVER";
        Vector2 size = MeasureTextEx(ui->font, dead_text, 40, 2);
        DrawTextEx(ui->font, dead_text, 
                   Vector2{(WINDOW_WIDTH - size.x) / 2, (WINDOW_HEIGHT - size.y) / 2}, 
                   40, 2, RED);
                   
        DrawTextEx(ui->font, "Pressione [R] para reiniciar", 
                   Vector2{(WINDOW_WIDTH - 200) / 2, (WINDOW_HEIGHT / 2) + 50}, 
                   16, 2, RAYWHITE);
    }
}