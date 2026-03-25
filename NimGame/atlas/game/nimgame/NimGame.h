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
        ~NimGame() = default;


        /*
            Das ist eine Integration — sie orchestriert nur den Ablauf durch den Aufruf von playRound() und isGameOver(), enthält aber keine eigene Logik/Berechnung. Der while-Ausdruck selbst ist dabei
            Steuerfluss, kein Business Logic.
        */
        auto play() -> void override { // Eine Methode ist eine Integration, wenn sie ausschließlich andere Methoden aufruft und koordiniert. Das ist hier der Fall.
            while (!isGameOver()) {
                playRound();
            }
        }

    private:
        int stones_;
        int move_;

        auto playRound() -> void { // Integration
            humanTurn();
            computerTurn();
        }

        auto humanTurn() -> void { // Integration
            if (isGameOver()) return;
            processHumanTurn();
            endTurn("Human");
        }

        auto processHumanTurn() -> void {
            do {
                askForMove();
            } while (!isMoveValid());
        }

        auto askForMove() -> void {
            readMove();
            reportIfMoveInvalid();
        }

        auto reportIfMoveInvalid() const -> void {
            if (!isMoveValid()) std::cout << "Ungueltiger Zug!\n";
        }

        auto readMove() -> void {
            std::cout << "Es gibt " << stones_ << " Steine. Bitte nehmen Sie 1, 2 oder 3!\n";
            std::cin >> move_;
        }

        auto computerTurn() -> void {
            if (isGameOver()) return;
            const int moves[] = {3, 1, 1, 2};
            move_ = moves[stones_ % 4];
            std::cout << "Computer nimmt " << move_ << " Steine." << std::endl;
            endTurn("Computer");
        }

        auto endTurn(const std::string &player) -> void { // Integration
            applyMove();
            handleGameEnd(player);
        }

        auto handleGameEnd(const std::string &player) const -> void {
            if (isGameOver()) {
                std::cout << player << " hat verloren" << std::endl;
            }
        }

        // ----------------------------------------- Implementierungssumpf -----------------------------

        auto isMoveValid() const noexcept -> bool {
            return move_ >= 1 && move_ <= 3;
        }

        auto applyMove() noexcept -> void {
            stones_ -= move_;
        }

        auto isGameOver() const noexcept -> bool {
            return stones_ < 1;
        }
    };
}
