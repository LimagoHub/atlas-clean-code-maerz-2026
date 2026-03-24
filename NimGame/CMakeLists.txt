cmake_minimum_required(VERSION 4.1)
project(NimGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(NimGame main.cpp
        atlas/game/IGame.h
        atlas/gameclient/Client.h
        atlas/game/nimgame/NimGame.h
)
