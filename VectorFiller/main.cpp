#include <iostream>
#include <memory>
#include <thread>
#include <exception>

#include "atlas/generator/impl/random/MersenneTwisterNumberGenerator.h"
#include "atlas/container/impl/sequential/VectorFactorySequentialImpl.h"
#include "atlas/container/impl/decorator/VectorFactoryBenchmarkDecorator.h"
#include "atlas/time/impl/StopwatchImpl.h"
#include "atlas/client/impl/ClientImpl.h"
#include "atlas/container/IVectorFactory.h"

using namespace atlas;
using generator::MersenneTwisterNumberGenerator;
using container::IVectorFactory;
using container::VectorFactorySequentialImpl;
using container::VectorFactoryBenchmarkDecorator;
using client::VectorClientImpl;
using time::StopwatchImpl;

/**
 * Orchestriert einen einzelnen Messdurchlauf.
 */
auto runMeasurement(size_t threadCount) -> void {
    auto generator = std::make_unique<MersenneTwisterNumberGenerator>();
    auto stopwatch = std::make_unique<StopwatchImpl>();

    std::unique_ptr<IVectorFactory<int>> factory = std::make_unique<VectorFactoryBenchmarkDecorator<int>>(
        std::make_unique<VectorFactorySequentialImpl<int>>(std::move(generator)),
        std::move(stopwatch));

    auto client = std::make_unique<VectorClientImpl>(std::move(factory));
    client->processVector();
}

auto main() -> int {
    try {
        const size_t maxThreads = std::thread::hardware_concurrency();

        std::cout << "==========================================" << std::endl;
        std::cout << "   ATLAS PERFORMANCE BENCHMARK (CLEAN)" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "Verfuegbare logische Kerne: " << maxThreads << "\n" << std::endl;

        runMeasurement(1);

        std::cout << "------------------------------------------" << std::endl;
        std::cout << "Saemtliche Messreihen erfolgreich abgeschlossen." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "\n!!! KRITISCHER FEHLER !!!" << std::endl;
        std::cerr << "Grund: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}