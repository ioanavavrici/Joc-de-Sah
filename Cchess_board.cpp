#include "Cchess_board.h"

namespace chess
{
    Cchess_board::Cchess_board()
    {
        m_board = std::array<std::array<chess_board_state, chess_board_width>, chess_board_height>{ {
            { p2_rook, p2_knight, p2_bishop, p2_queen, p2_king, p2_bishop, p2_knight, p2_rook },
            { p2_pawn, p2_pawn,   p2_pawn,   p2_pawn,  p2_pawn, p2_pawn,   p2_pawn,   p2_pawn },
            { empty,   empty,     empty,     empty,    empty,   empty,     empty,     empty },
            { empty,   empty,     empty,     empty,    empty,   empty,     empty,     empty },
            { empty,   empty,     empty,     empty,    empty,   empty,     empty,     empty },
            { empty,   empty,     empty,     empty,    empty,   empty,     empty,     empty },
            { p1_pawn, p1_pawn,   p1_pawn,   p1_pawn,  p1_pawn, p1_pawn,   p1_pawn,   p1_pawn },
            { p1_rook, p1_knight, p1_bishop, p1_queen, p1_king, p1_bishop, p1_knight, p1_rook }
            }};

        m_invert_y = chess_board_height - 1;
    }

    game_result Cchess_board::game_state() const
    {
        // check for p1 win
        if (!find_figure(p2_king))
        {
            return p1_win;
        }

        // check for p2 win
        if (!find_figure(p1_king))
        {
            return p2_win;
        }

        return still_playing;
    }

    void Cchess_board::display() const
    {
        std::unordered_map<chess_board_state, std::string> figure_to_string = {
        {empty,"empty       "}, {p1_pawn,"white_pawn  "}, {p1_knight,"white_knight"}, {p1_bishop,"white_bishop"}, {p1_rook,"white_rook  "}, {p1_queen,"white_queen "}, {p1_king,"white_king  "},
                                {p2_pawn,"black_pawn  "}, {p2_knight,"black_knight"}, {p2_bishop,"black_bishop"}, {p2_rook,"black_rook  "}, {p2_queen,"black_queen "}, {p2_king,"black_king  "}
        };

        std::array<int32_t, chess_board_height> y_axis_descr = { 8, 7, 6, 5, 4, 3, 2, 1 };

        // print x-axis description
        std::cout << "  a             b             c             d             e             f             g             h\n";

        // print line by line
        for (int32_t i = 0; i < chess_board_height; i++)
        {
            std::cout << static_cast<int>(y_axis_descr[i]) << " ";
            for (chess_board_state state : m_board[i])
            {
                std::cout << figure_to_string[state].c_str() << "  ";
            }
            std::cout << "\n";
        }

    }

    bool Cchess_board::is_valid(std::pair<int32_t, int32_t> from, std::pair<int32_t, int32_t> to, bool player_switch) const
    {
        int32_t from_x = from.first;
        int32_t from_y = m_invert_y - from.second;
        int32_t to_x = to.first;
        int32_t to_y = m_invert_y - to.second;

        std::pair<chess_board_state, chess_board_state> figure_range;

        // change range of own figures depending on player switch
        if (player_switch)
        {
            figure_range.first = p1_pawn;
            figure_range.second = p1_king;
        }
        else
        {
            figure_range.first = p2_pawn;
            figure_range.second = p2_king;
        }

        // check if move is valid based on figure
        // switch statement was not possible, because it requires compile-time constants

        // pawn
        if (m_board[from_y][from_x] == figure_range.first)
        {
            if ((is_relative_field(from, to,  0, -1) && m_board[to_y][to_x] == empty && player_switch)                                  || // 1 forward - player 1
                (is_relative_field(from, to,  0, -2) && m_board[to_y][to_x] == empty && from_y == 6                  && player_switch)  || // 2 forward from start - player 1
                (is_relative_field(from, to, -1, -1) && !is_mate(to, figure_range)   && m_board[to_y][to_x] != empty && player_switch)  || // attack diagonal - player 1
                (is_relative_field(from, to,  1, -1) && !is_mate(to, figure_range)   && m_board[to_y][to_x] != empty && player_switch)  || // attack diagonal - player 1

                (is_relative_field(from, to,  0,  1) && m_board[to_y][to_x] == empty && !player_switch)                                 || // 1 forward - player 2
                (is_relative_field(from, to,  0,  2) && m_board[to_y][to_x] == empty && from_y == 1                  && !player_switch) || // 2 forward from start - player 2
                (is_relative_field(from, to, -1,  1) && !is_mate(to, figure_range)   && m_board[to_y][to_x] != empty && !player_switch) || // attack diagonal - player 2
                (is_relative_field(from, to,  1,  1) && !is_mate(to, figure_range)   && m_board[to_y][to_x] != empty && !player_switch))   // attack diagonal - player 2
            {
                return true;
            }
        }
        // knight
        else if (m_board[from_y][from_x] == figure_range.first + 1)
        {
            if ((is_relative_field(from, to, -1, -2) && !is_mate(to, figure_range)) || // 2 up, 1 left
                (is_relative_field(from, to,  1, -2) && !is_mate(to, figure_range)) || // 2 up, 1 right
                (is_relative_field(from, to, -1,  2) && !is_mate(to, figure_range)) || // 2 down, 1 left
                (is_relative_field(from, to,  1,  2) && !is_mate(to, figure_range)) || // 2 down, 1 right
                (is_relative_field(from, to,  2, -1) && !is_mate(to, figure_range)) || // 2 right, 1 up
                (is_relative_field(from, to,  2,  1) && !is_mate(to, figure_range)) || // 2 right, 1 down
                (is_relative_field(from, to, -2, -1) && !is_mate(to, figure_range)) || // 2 left, 1 up
                (is_relative_field(from, to, -2,  1) && !is_mate(to, figure_range)))   // 2 left, 1 down
            {
                return true;
            }
        }
        // bishop
        else if (m_board[from_y][from_x] == figure_range.first + 2)
        {
            if (check_diagonal_move(from, to) && !is_mate(to, figure_range))
            {
                return true;
            }
        }
        // rook
        else if (m_board[from_y][from_x] == figure_range.first + 3)
        {
            if (check_linear_move(from, to) && !is_mate(to, figure_range))
            {
                return true;
            }
        }
        // queen
        else if (m_board[from_y][from_x] == figure_range.first + 4)
        {
            if ((check_diagonal_move(from, to) || check_linear_move(from, to)) && !is_mate(to, figure_range))
            {
                return true;
            }
        }
        // king
        else if (m_board[from_y][from_x] == figure_range.first + 5)
        {

            if ((is_relative_field(from, to,  0, -1) && !is_mate(to, figure_range)) || // 1 up
                (is_relative_field(from, to,  1, -1) && !is_mate(to, figure_range)) || // 1 up, 1 right
                (is_relative_field(from, to, -1, -1) && !is_mate(to, figure_range)) || // 1 up, 1 left
                (is_relative_field(from, to,  1,  0) && !is_mate(to, figure_range)) || // 1 right
                (is_relative_field(from, to, -1,  0) && !is_mate(to, figure_range)) || // 1 left
                (is_relative_field(from, to,  0,  1) && !is_mate(to, figure_range)) || // 1 down
                (is_relative_field(from, to,  1,  1) && !is_mate(to, figure_range)) || // 1 down, 1 right
                (is_relative_field(from, to, -1,  1) && !is_mate(to, figure_range)))   // 1 down, 1 left
            {
                return true;
            }
        }
        else
        {
            std::cout << "\nThis is not one of your figures.\n\n";
            return false;
        }

        std::cout << "\nNot a valid move.\n\n";

        return false;
    }

    bool Cchess_board::is_relative_field(std::pair<int32_t, int32_t> from, std::pair<int32_t, int32_t> to, int32_t x_shift, int32_t y_shift) const
    {
        return (m_invert_y - from.second + y_shift == m_invert_y - to.second &&
                from.first               + x_shift == to.first              );
    }

    bool Cchess_board::is_mate(std::pair<int32_t, int32_t> field, std::pair<chess_board_state, chess_board_state> figure_range) const
    {
        return !(m_board[m_invert_y - field.second][field.first] < figure_range.first ||
                 m_board[m_invert_y - field.second][field.first] > figure_range.second);
    }

    bool Cchess_board::check_linear_move(std::pair<int32_t, int32_t> from, std::pair<int32_t, int32_t> to) const
    {
        // is linear?
        if (from.first == to.first || m_invert_y - from.second == m_invert_y - to.second)
        {
            int32_t temp_x = from.first;
            int32_t temp_y = m_invert_y - from.second;

            // is valid?
            // x-axis case
            while (temp_x != to.first)
            {
                if (temp_x > to.first)
                {
                    temp_x--;
                }
                else
                {
                    temp_x++;
                }

                if (m_board[m_invert_y - from.second][temp_x] != empty && temp_x != to.first)
                {
                    return false;
                }
            }


            // y-axis case
            while (temp_y != m_invert_y - to.second)
            {
                if (temp_y > m_invert_y - to.second)
                {
                    temp_y--;
                }
                else
                {
                    temp_y++;
                }

                if (m_board[temp_y][from.first] != empty && temp_y != m_invert_y - to.second)
                {
                    return false;
                }
            }

            return true;
        }

        return false;
    }

    bool Cchess_board::check_diagonal_move(std::pair<int32_t, int32_t> from, std::pair<int32_t, int32_t> to) const
    {
        int32_t temp_x = from.first;
        int32_t temp_y = m_invert_y - from.second;

        // is diagonal?
        if (abs((m_invert_y - from.second) - (m_invert_y - to.second)) == abs(from.first - to.first))
        {
            // is valid?
            while (temp_x != to.first)
            {
                if (temp_x > to.first)
                {
                    temp_x--;
                }
                else
                {
                    temp_x++;
                }

                if (temp_y > m_invert_y - to.second)
                {
                    temp_y--;
                }
                else
                {
                    temp_y++;
                }

                if (m_board[temp_y][temp_x] != empty && temp_x != to.first)
                {
                    return false;
                }
            }

            return true;
        }

        return false;
    }

    void Cchess_board::move(std::pair<int32_t, int32_t> from, std::pair<int32_t, int32_t> to)
    {
        // assign figure to new position
        m_board[m_invert_y - to.second][to.first] = m_board[m_invert_y - from.second][from.first];

        // clear old position
        m_board[m_invert_y - from.second][from.first] = empty;
    }

    bool Cchess_board::find_figure(chess_board_state figure) const
    {
        for (auto& row : m_board)
        {
            if (std::find(row.begin(), row.end(), figure) != row.end())
            {
                return true;
            }
        }
        return false;
    }
}
