#include <iostream>
#include "atlas/gameclient/Client.h"
#include "atlas/game/nimgame/NimGame.h"
#include "atlas/game/nimgame/player/ComputerPlayer.h"
#include "atlas/game/nimgame/player/HumanPlayer.h"

using Game = atlas::game::IGame;
using GameClient = atlas::gameclient::Client;
using NimGame = atlas::game::nimgame::NimGame;
using HumanPlayer = atlas::game::nimgame::player::HumanPlayer;
using ComputerPlayer = atlas::game::nimgame::player::ComputerPlayer;
using Writer = atlas::io::ConsoleWriter;

// RAII-konforme Implementierung (Resource Acquisition Is Initialization)
void run();

int main() {
    try {
        run();

    } catch (const std::invalid_argument& e) {
        std::cerr << "Konfigurationsfehler: " << e.what() << std::endl;
        return 1;
    } catch (const std::runtime_error& e) {
        std::cerr << "Laufzeitfehler während des Spiels: " << e.what() << std::endl;
        return 2;
    } catch (const std::exception& e) {
        std::cerr << "Unerwarteter Fehler: " << e.what() << std::endl;
        return 3;
    } catch (...) {
        std::cerr << "Ein unbekannter kritischer Fehler ist aufgetreten!" << std::endl;
        return -1;
    }
    return 0;
}

void run() {

    auto writer = std::make_unique<Writer>();
    auto human = std::make_unique<HumanPlayer>("Horst");
    auto computer = std::make_unique<ComputerPlayer>("HAL");

    auto game = std::make_unique<atlas::game::nimgame::NimGame>(std::move(writer));
    game->addPlayer(std::move(human));
    game->addPlayer(std::move(computer));
    GameClient client{std::move(game)};
    client.go();

}
