//
// Created by JoachimWagner on 25.03.2026.
//

#pragma once
#include <iostream>

#include "AbstractNimGamePlayer.h"

namespace atlas::game::nimgame::player {
    class HumanPlayer: public AbstractNimGamePlayer {

        public:
        using AbstractNimGamePlayer::AbstractNimGamePlayer;

        [[nodiscard]] auto makeMove(const int &stones) const -> int override {
            int move;
            std::cout << "Es gibt " << stones << " Steine. Bitte nehmen Sie 1, 2 oder 3!\n";
            std::cin >> move;
            return move;
        }
    };
}
