//
// Created by JoachimWagner on 24.03.2026.
//

#pragma once
#include <memory>

#include "../game/IGame.h"

namespace atlas::gameclient {
    using Game = atlas::game::IGame;
    class Client {
    public:
        explicit Client(std::unique_ptr<Game> game)
            : game(std::move(game)) {
        }

        virtual ~Client() = default;
        auto go() -> void {
            game->play();
        }

    private:
        std::unique_ptr<Game> game;

    };
} // gameclient