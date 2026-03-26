//
// Created by JoachimWagner on 25.03.2026.
//

#pragma once
#include "IGame.h"
#include "player/IPlayer.h"
#include "../io/Writer.h"

namespace atlas::game {
    template<class BOARD, class MOVE>
    class AbstractGame: public IGame {
        using Player = player::IPlayer<BOARD, MOVE>;
        using PlayerPointer = std::unique_ptr<Player>;
        using Writer = std::unique_ptr<io::Writer>;

    public:
        explicit AbstractGame(Writer writer)
            : writer_(std::move(writer)) {
        }

        /*
                Das ist eine Integration — sie orchestriert nur den Ablauf durch den Aufruf von playRound() und isGameOver(),
                enthält aber keine eigene Logik/Berechnung. Der while-Ausdruck selbst ist dabei
                Steuerfluss, kein Business Logic.
            */
        auto play() -> void override { // Eine Methode ist eine Integration, wenn sie ausschließlich andere Methoden aufruft und koordiniert. Das ist hier der Fall.
            while (!isGameOver()) playRound();
        }

        auto addPlayer(PlayerPointer player) -> void { players_.push_back(std::move(player)); }


        auto removePlayer(PlayerPointer player) -> void {
            // TODO implement later
            //int n = 5;
        }

    private:
        std::vector<PlayerPointer> players_;
        BOARD board_;
        MOVE move_;

        Player *currentPlayer_{nullptr};

        Writer writer_;
        auto playRound() -> void { // Integration
            for (auto &player : players_) {
                currentPlayer_ = player.get();
                playersTurn();
            }
        }

        auto playersTurn() -> void { // Integration
            if (isGameOver()) return;
            processPlayerTurn();
            endTurn();
        }

        auto processPlayerTurn() -> void {
            do askForMove(); while (!isMoveValid());
        }


        auto askForMove() -> void {
            move_ = currentPlayer_->makeMove(board_);
            reportIfMoveInvalid();
        }

        auto reportIfMoveInvalid() const -> void {
            if (!isMoveValid()) write( "Ungueltiger Zug!\n");
        }


        auto endTurn() -> void { // Integration
            applyMove();
            handleGameEnd();
        }

        auto handleGameEnd() const -> void {
            if (isGameOver()) {
                write(currentPlayer_->getName() + " hat verloren\n");

            }
        }

    protected:
        auto getPlayers() const -> const std::vector<PlayerPointer>& {
            return players_;
        }


        auto getBoard() const -> const BOARD& {
            return board_;
        }

        auto getMove() const -> const MOVE& {
            return move_;
        }

        auto setBoard(const BOARD &board) -> void {
            board_ = board;
        }

        auto setMove(const MOVE &move) -> void {
            move_ = move;
        }

        auto write(const std::string &message) const  -> void {
            writer_->write(message);
        }

        [[nodiscard]] virtual auto isGameOver() const noexcept -> bool = 0;

        [[nodiscard]] virtual auto isMoveValid() const noexcept -> bool = 0;

        virtual auto applyMove() noexcept -> void = 0;
    };
}