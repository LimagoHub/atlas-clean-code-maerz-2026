cmake_minimum_required(VERSION 4.1)
project(NimGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(NimGame main.cpp
        atlas/game/IGame.h
        atlas/gameclient/Client.h
        atlas/game/nimgame/NimGame.h
        atlas/game/nimgame/player/AbstractNimGamePlayer.h
        atlas/game/nimgame/player/HumanPlayer.h
        atlas/game/nimgame/player/ComputerPlayer.h
        atlas/io/Writer.h
        atlas/io/ConsoleWriter.h
        atlas/game/player/IPlayer.h
        atlas/game/player/AbstractPlayer.h
        atlas/game/AbstractGame.h
)
