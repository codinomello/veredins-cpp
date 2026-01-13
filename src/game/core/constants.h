#ifndef GAME_CORE_CONSTANTS_H
#define GAME_CORE_CONSTANTS_H

#include <string>

#include "types.h"

// janela
inline constexpr i32 WINDOW_WIDTH = 1280;
inline constexpr i32 WINDOW_HEIGHT = 720;

// veredins
inline constexpr u32 INITIAL_VEREDIM_COUNT = 3;
inline constexpr u32 MAX_VEREDIM_COUNT = 3;

// level
inline constexpr u32 XP_PER_LEVEL = 100;
inline constexpr u32 MAX_LEVEL = 50;

// mapa
inline constexpr u32 MAP_WIDTH = 64;
inline constexpr u32 MAP_HEIGHT = 64;

// fonte
inline constexpr u32 UI_FONT_SIZE = 16;
inline constexpr f32 UI_MARGIN = 8;

// caminhos
inline const std::string FONT_PATH = "assets/fonts/helvetica/Helvetica.ttf";
inline const std::string WINDOW_ICON_PATH = "assets/images/icons/path.png";

#endif // GAME_CORE_CONSTANTS_H