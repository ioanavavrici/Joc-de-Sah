#ifndef CPLAYER_H
#define CPLAYER_H

#include "game_constants.h"
#include <utility>
#include <string>
#include <iostream>
#include <ctype.h>
#include <unordered_map>

namespace chess
{
    class Cplayer
    {
    public:

        std::pair<int32_t, int32_t> get_pos() const;

    };
#endif
}
