#include "Cchess_game.h"

namespace chess
{
    game_result Cchess_game::play()
    {
        game_result result;
        std::pair<int32_t, int32_t> from_coords;
        std::pair<int32_t, int32_t> to_coords;
        Cplayer* player = nullptr;

        do
        {
            // get pointer to current player to avoid repetition
            if (m_player_switch)
            {
                player = &m_player1;
            }
            else
            {
                player = &m_player2;
            }

            // display current game state
            m_board.display();
            std::cout << "\n\n";

            std::cout << "Player " << !m_player_switch + 1 << "'s turn: \n\n";

            // get move info until move is valid
            do
            {
                std::cout << "Please enter the position of the figure you want to move: ";
                from_coords = player->get_pos();
                std::cout << "Please enter the position you want your figure to move to: ";
                to_coords = player->get_pos();

            } while (!m_board.is_valid(from_coords, to_coords, m_player_switch));

            // execute move and update board
            m_board.move(from_coords, to_coords);

            // switch player
            m_player_switch = !m_player_switch;

            // clear console
            std::cout << std::flush;
            system("CLS");

        } while ((result = m_board.game_state()) == still_playing);

        return result;
    }
}
