//
// Created by JoachimWagner on 25.03.2026.
//

#pragma once
#include "../../player/AbstractPlayer.h"

namespace atlas::game::nimgame::player {
    class AbstractNimGamePlayer: public game::player::AbstractPlayer<int, int> {

        public:
        explicit AbstractNimGamePlayer(const std::string &name)
            : AbstractPlayer<int, int>(name) {
        }


    };
}
