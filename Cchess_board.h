#include "game_constants.h"
#include <array>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <stdlib.h>

namespace chess
{
    class Cchess_board
    {
    public:

        Cchess_board(); // initialise default chess board
        game_result game_state() const; // return current game state
        void display() const; // display current board in console
        bool is_valid(std::pair<int32_t, int32_t> from, std::pair<int32_t, int32_t> to, bool player_switch) const; // return true if move is valid
        void move(std::pair<int32_t, int32_t> from, std::pair<int32_t, int32_t> to); // execute move

    private:

        bool find_figure(chess_board_state figure) const; // return true if figure is in board
        bool is_relative_field(std::pair<int32_t, int32_t> from, std::pair<int32_t, int32_t> to, int32_t x_shift, int32_t y_shift) const; // return true if position "to" is relative to "from" with shifts
        bool is_mate(std::pair<int32_t, int32_t> field, std::pair<chess_board_state, chess_board_state> figure_range) const; // return true if field is mate
        bool check_linear_move(std::pair<int32_t, int32_t> from, std::pair<int32_t, int32_t> to) const; // return true if move is linear and valid
        bool check_diagonal_move(std::pair<int32_t, int32_t> from, std::pair<int32_t, int32_t> to) const; // return true if move is diagonal and valid

        std::array<std::array<chess_board_state, chess_board_width>, chess_board_height> m_board;
        int32_t m_invert_y; // help value to distract from to invert index

    };
#endif
}
