#include "Cplayer.h"

namespace chess
{
    std::pair<int32_t, int32_t> Cplayer::get_pos() const
    {
        // dictionary to convert x-axis char to integer index
        std::unordered_map<char, int32_t> convert_to_int({ {'a',0}, {'b',1}, {'c',2}, {'d',3}, {'e',4}, {'f',5}, {'g',6}, {'h',7} });

        std::string pos;

        // get valid user input
        for (;;)
        {
            std::cin >> pos;
            // check for
            //  size               a-h                                                    <= 8               >= 1
            if (pos.size() == 2 && convert_to_int.find(pos[0]) != convert_to_int.end() && pos[1] - '0' <= 8 && pos[1] - '0' >= 1)
            {
                return { convert_to_int[pos[0]], pos[1] - '0' - 1 };
            }
            std::cout << "\nInvalid input format.\n\n";
        }
    }
}
