//
// Created by JoachimWagner on 25.03.2026.
//

#pragma once
#include "AbstractNimGamePlayer.h"

namespace atlas::game::nimgame::player {
    class ComputerPlayer : public AbstractNimGamePlayer{

        static inline const int optimalMoves[] = {3,1,1,2};
        public:
        using AbstractNimGamePlayer::AbstractNimGamePlayer;

        [[nodiscard]] auto makeMove(const int &stones) const -> int override {
            const int move = optimalMoves[stones % 4];
            std::cout << this->getName() << " nimmt " << move << " Steine!" << std::endl;
            return move;
        }
    };
}
