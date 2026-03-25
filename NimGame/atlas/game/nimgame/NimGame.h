//
// Created by JoachimWagner on 24.03.2026.
//

#pragma once
#include <iostream>
#include <vector>

#include "../AbstractGame.h"

#include "../../io/ConsoleWriter.h"


namespace atlas::game::nimgame {


    using Writer = std::unique_ptr<atlas::io::Writer>;
    class NimGame: public AbstractGame<int, int> {

    public:
        explicit NimGame(std::unique_ptr<io::Writer> writer) : AbstractGame<int, int>(std::move(writer)) {
            set_board(23);
        }


    protected:


        // ----------------------------------------- Implementierungssumpf -----------------------------

        auto isMoveValid() const noexcept -> bool {
            return get_move() >= 1 && get_move() <= 3;
        }

        auto applyMove() noexcept -> void {
            set_board(get_board()-get_move());
        }

        auto isGameOver() const noexcept -> bool {
            return get_board() < 1 || getPlayers().size() == 0;
        }
    };
}
