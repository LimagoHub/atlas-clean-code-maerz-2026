cmake_minimum_required(VERSION 4.1)
project(VectorFiller)

set(CMAKE_CXX_STANDARD 17)

add_executable(VectorFiller main.cpp
        atlas/client/IClient.h
        atlas/container/IVectorFactory.h
        atlas/generator/IGenerator.h
        atlas/time/IStopwatch.h
        atlas/client/impl/ClientImpl.h
        atlas/generator/impl/random/MersenneTwisterNumberGenerator.h
        atlas/generator/impl/generic/GenericGeneratorImpl.h
        atlas/container/AbstractVectorFactory.h
        atlas/container/impl/sequential/VectorFactorySequentialImpl.h
        atlas/container/impl/decorator/VectorFactoryLoggerDecorator.h
        atlas/container/impl/decorator/VectorFactorySecureDecorator.h)
