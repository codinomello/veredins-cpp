#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <string>

#include "game/core/types.h"

// constantes
inline constexpr i32 WINDOW_WIDTH = 1280;
inline constexpr i32 WINDOW_HEIGHT = 720;
inline constexpr i32 MAP_WIDTH = 64;
inline constexpr i32 MAP_HEIGHT = 64;
inline constexpr f32 UI_FONT_SIZE = 16;
inline constexpr f32 UI_MARGIN = 8;

// caminhos
inline const std::string FONT_PATH = "assets/fonts/nunito/Nunito-Regular.ttf";
inline const std::string WINDOW_ICON_PATH = "assets/images/icons/path.png";

#endif // GAME_CONSTANTS_H