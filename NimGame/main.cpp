#include <iostream>
#include "atlas/gameclient/Client.h"
#include "atlas/game/nimgame/NimGame.h"

using Game = atlas::game::IGame;
using GameClient = atlas::gameclient::Client;
using NimGame = atlas::game::nimgame::NimGame;
int main() {
    std::unique_ptr<Game> game;
    game = std::make_unique<atlas::game::nimgame::NimGame>();
    GameClient client{std::move(game)};
    client.go();
    return 0;
}
