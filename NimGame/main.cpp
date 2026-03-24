#include <iostream>
#include "atlas/gameclient/Client.h"
#include "atlas/game/nimgame/NimGame.h"

using GAME = atlas::game::IGame;
using CLIENT = atals::gameclient::Client;
int main() {
    std::unique_ptr<GAME> game;
    game = std::make_unique<atlas::game::nimgame::NimGame>();
    CLIENT client{std::move(game)};
    client.go();
    return 0;
}