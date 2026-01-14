#ifndef GAME_CORE_CONSTANTS_H
#define GAME_CORE_CONSTANTS_H

#include <string>

#include "types.h"

// janela
inline constexpr i32 WINDOW_WIDTH = 1280;
inline constexpr i32 WINDOW_HEIGHT = 720;
inline constexpr char* WINDOW_ICON_PATH = "assets/images/icons/path.png";

// veredins
inline constexpr u32 INITIAL_VEREDIM_COUNT = 70;
inline constexpr u32 MAX_VEREDIM_COUNT = 50;

// level
inline constexpr u32 XP_PER_LEVEL = 100;
inline constexpr u32 MAX_LEVEL = 50;

// mapa
inline constexpr u32 MAP_WIDTH = 64;
inline constexpr u32 MAP_HEIGHT = 64;

// ladrilho
inline constexpr u32 TILE_SIZE = 32;

// fonte
inline constexpr u32 UI_FONT_SIZE = 16;
inline constexpr f32 UI_MARGIN = 8;
inline constexpr char* FONT_PATH = "assets/fonts/helvetica.ttf";

#endif // GAME_CORE_CONSTANTS_H