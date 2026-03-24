//
// Created by JoachimWagner on 24.03.2026.
//

#pragma once
#include <iostream>
#include "../IGame.h"

namespace atlas::game::nimgame {
    class NimGame: public IGame {

    public:
        NimGame():stones_{23}{};
        virtual ~NimGame() = default;

        auto play() -> void override {
            while (! isGameOver()) {
                playRound();
            }
        }

    private:
        int stones_;

        auto playRound() -> void {
            humanMove();
            computerMove();
        }

        auto humanMove() -> void {
            int turn;
            while (true) {
                std::cout << "Es gibt " << stones_ <<  " Steine. Bitte nehmen Sie 1, 2 oder 3!\n";
                std::cin >> turn;
                if ( turn >=1 && turn <= 3) break;
                std::cout << "Ungueltiger Zug!\n";
            }
            stones_-= turn;
        }
        auto computerMove() -> void {
            if (isGameOver()) {
                std::cout << "Du Loser!\n";
                return;
            }
            if (stones_ == 1) {
                stones_--;
                std::cout << "Du hast nur Glueck gehabt\n";
                return;
            }

            const int zuege [] = {3,1,1,2};
            const int turn = zuege[stones_ % 4];;
            std::cout << "Computer nimmt " << turn << "Steine." << std::endl;
            stones_ -= turn;
        }
        auto isGameOver() -> bool {
            return stones_ < 1;
        }
    };
}
