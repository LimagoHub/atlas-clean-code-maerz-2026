cmake_minimum_required(VERSION 4.1)
project(VectorFiller)

set(CMAKE_CXX_STANDARD 17)

add_executable(VectorFiller main.cpp
        atlas/client/IClient.h
        atlas/container/IVectorFactory.h
        atlas/generator/IGenerator.h
        atlas/time/IStopwatch.h)
