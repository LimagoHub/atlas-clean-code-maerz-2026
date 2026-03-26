//
// Created by JoachimWagner on 12.03.2025.
//

#pragma once
#include <memory>
#include <iostream>
#include "../../VectorFactory.h"
#include "../../../time/Stopwatch.h"
namespace atlas::container {

    template<class T>
    class VectorFactoryBenchmarkDecorator: public VectorFactory<T>{
        using VECTOR_POINTER = std::shared_ptr<std::vector<T>>;
    public:
        VectorFactoryBenchmarkDecorator(
                std::unique_ptr<VectorFactory<T>> vectorFactory,
                std::unique_ptr<atlas::time::Stopwatch> stopwatch) : _vectorFactory(
                std::move(vectorFactory)), _stopwatch(std::move(stopwatch)) {}

        VECTOR_POINTER createAndFillVector(const size_t size) noexcept override {
            _stopwatch->start();
            auto result =  _vectorFactory->createAndFillVector(size);
            _stopwatch->stop();
            std::cout << "Duration = " << _stopwatch->getDuration().count() << std::endl;
            return result;
        }

    private:
        std::unique_ptr<VectorFactory<T>> _vectorFactory;
        std::unique_ptr<atlas::time::Stopwatch> _stopwatch;
    };

}
