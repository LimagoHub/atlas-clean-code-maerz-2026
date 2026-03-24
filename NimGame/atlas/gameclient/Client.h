//
// Created by JoachimWagner on 24.03.2026.
//

#pragma once
#include <memory>

#include "../game/IGame.h"

namespace atals::gameclient {
    using GAME = atlas::game::IGame;
    class Client {
    public:
        explicit Client(std::unique_ptr<GAME> game)
            : game(std::move(game)) {
        }

        virtual ~Client() = default;
        void go() {
            game->play();
        }

    private:
        std::unique_ptr<GAME> game;

    };
} // gameclient