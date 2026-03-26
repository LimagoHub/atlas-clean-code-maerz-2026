//
// Created by JoachimWagner on 24.03.2026.
//

#pragma once
#include <iostream>
#include <vector>

#include "../AbstractGame.h"

#include "../../io/ConsoleWriter.h"


namespace atlas::game::nimgame {


    using Writer = std::unique_ptr<io::Writer>;
    class NimGame: public AbstractGame<int, int> {

    public:
        explicit NimGame(std::unique_ptr<io::Writer> writer) : AbstractGame(std::move(writer)) {
            setBoard(23);
        }


    protected:


        // ----------------------------------------- Implementierungssumpf -----------------------------

        [[nodiscard]] auto isMoveValid() const noexcept -> bool  override {
            return getMove() >= 1 && getMove() <= 3;
        }

        auto applyMove() noexcept -> void  override {
            setBoard(getBoard() - getMove());
        }

        [[nodiscard]] auto isGameOver() const noexcept -> bool  override {
            return getBoard() < 1 || getPlayers().empty();
        }
    };
}
