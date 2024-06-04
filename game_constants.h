#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include <stdint.h>

constexpr int32_t chess_board_height = 8;
constexpr int32_t chess_board_width = 8;

enum chess_board_state
{
    empty = 0,

    p1_pawn = 1,
    p1_knight,
    p1_bishop,
    p1_rook,
    p1_queen,
    p1_king,

    p2_pawn = 11,
    p2_knight,
    p2_bishop,
    p2_rook,
    p2_queen,
    p2_king,
};

enum game_result
{
    draw = 0, p1_win, p2_win, still_playing
};

#endif
