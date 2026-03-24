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
        int turn_;

        auto playRound() -> void {// Integration
            humanMove();
            computerMove();
        }

        auto humanMove() -> void {

            if (isGameOver()) return;


            while (true) {
                std::cout << "Es gibt " << stones_ <<  " Steine. Bitte nehmen Sie 1, 2 oder 3!\n";
                std::cin >> turn_;
                if ( turn_ >=1 && turn_ <= 3) break;
                std::cout << "Ungueltiger Zug!\n";
            }
            terminateMove( "Human");
        }



        auto computerMove() -> void {

            if (isGameOver()) return;

            const int zuege [] = {3,1,1,2};
            turn_ = zuege[stones_ % 4];;
            std::cout << "Computer nimmt " << turn_ << "Steine." << std::endl;
            terminateMove( "Computer");
        }




        auto terminateMove( const std::string &player)-> void { // Integration
            applyMove();
            handleGameEnd(player);
        }

        auto handleGameEnd(const std::string &player)-> void {
            if (isGameOver()) {
                std::cout << player << " hat verloren"  << std::endl;
            }
        }
        // ----------------------------------------- Implementierungssumpf -----------------------------
        auto applyMove() -> void{
            stones_ -= turn_;
        }

        auto isGameOver() -> bool {
            return stones_ < 1;
        }
    };
}
