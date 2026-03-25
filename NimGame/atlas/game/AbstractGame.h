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
        using Writer = std::unique_ptr<atlas::io::Writer>;

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


        auto  get_board() const -> const  BOARD& {
            return board_;
        }



        auto get_move() const -> const MOVE& {
            return move_;
        }


        void set_board(const BOARD &board) {
            board_ = board;
        }

        void set_move(const MOVE &move) {
            move_ = move;
        }

    protected:
        auto write(const std::string &message) const  -> void {
            writer_->write(message);
        }

        virtual auto isGameOver() const noexcept -> bool = 0;

        virtual auto isMoveValid() const noexcept -> bool = 0;

        virtual auto applyMove() noexcept -> void = 0;
    };
}