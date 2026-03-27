cmake_minimum_required(VERSION 4.1)
project(VectorFiller)

set(CMAKE_CXX_STANDARD 17)

add_executable(VectorFiller main.cpp
        src/atlas/client/IClient.h
        src/atlas/container/IVectorFactory.h
        src/atlas/generator/IGenerator.h
        src/atlas/time/IStopwatch.h
        src/atlas/client/impl/ClientImpl.h
        src/atlas/generator/impl/random/MersenneTwisterNumberGenerator.h
        src/atlas/generator/impl/generic/GenericGeneratorImpl.h
        src/atlas/container/AbstractVectorFactory.h
        src/atlas/container/impl/sequential/VectorFactorySequentialImpl.h
        src/atlas/container/impl/decorator/VectorFactoryLoggerDecorator.h
        src/atlas/container/impl/decorator/VectorFactorySecureDecorator.h
        src/atlas/container/impl/builder/VectorFactoryBuilder.h
        src/atlas/threadpool/thread_pool.hpp
        src/atlas/generator/IGeneratorFactory.h
        src/atlas/container/impl/parallel/VectorFactoryParallelImpl.h
        src/atlas/container/impl/parallel/VectorFactoryAutoImpl.h
        src/atlas/container/impl/parallel/VectorFactoryThreadpoolImpl.h
        src/atlas/container/impl/parallel/VectorFactoryThreadpoolLoopImpl.h)

enable_testing()
add_subdirectory(tests)
