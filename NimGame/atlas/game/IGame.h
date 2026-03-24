//
// Created by JoachimWagner on 24.03.2026.
//

#pragma once

namespace atlas::game {
    class IGame {
        public:
        virtual ~IGame() = default;
        virtual void play() = 0;
    };
}