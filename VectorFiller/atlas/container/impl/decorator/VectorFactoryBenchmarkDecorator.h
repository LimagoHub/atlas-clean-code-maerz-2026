//
// Created by JoachimWagner on 12.03.2025.
//

#pragma once
#include <memory>
#include <iostream>
#include "../../IVectorFactory.h"
#include "../../../time/IStopwatch.h"
namespace atlas::container {

    template<class T>
    class VectorFactoryBenchmarkDecorator: public IVectorFactory<T>{
        using VECTOR_POINTER = std::shared_ptr<std::vector<T>>;
    public:
        VectorFactoryBenchmarkDecorator(
                std::unique_ptr<IVectorFactory<T>> vectorFactory,
                std::unique_ptr<atlas::time::IStopwatch> stopwatch) : _vectorFactory(
                std::move(vectorFactory)), _stopwatch(std::move(stopwatch)) {}

        auto createAndFillVector(const size_t size) noexcept -> VECTOR_POINTER override {
            _stopwatch->start();
            auto result =  _vectorFactory->createAndFillVector(size);
            _stopwatch->stop();
            std::cout << "Duration = " << _stopwatch->getDuration().count() << std::endl;
            return result;
        }

    private:
        std::unique_ptr<IVectorFactory<T>> _vectorFactory;
        std::unique_ptr<atlas::time::IStopwatch> _stopwatch;
    };

}
