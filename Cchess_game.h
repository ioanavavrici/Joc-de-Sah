#ifndef CCHESS_GAME_H
#define CCHESS_GAME_H

#include "Cchess_board.h"
#include "Cplayer.h"

namespace chess
{
    class Cchess_game
    {
    public:

        Cchess_game() : m_player1{ Cplayer() }, m_player2{ Cplayer() }, m_board{ Cchess_board() }, m_player_switch{ true }{};
        game_result play(); // play single game of chess and return 1,2 for winner and 0 for draw

    private:

        Cplayer m_player1;
        Cplayer m_player2;
        Cchess_board m_board;
        bool m_player_switch;

    };
#endif
}
