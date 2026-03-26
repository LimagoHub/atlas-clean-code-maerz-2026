//
// Created by JoachimWagner on 12.03.2025.
//

#pragma once
#include <memory>
#include <iostream>
#include "../../IVectorFactory.h"

namespace atlas::container {

    template<class T>
    class VectorFactoryLoggerDecorator: public IVectorFactory<T>{
        using VECTOR_POINTER = std::shared_ptr<std::vector<T>>;
    public:
        VectorFactoryLoggerDecorator(
                std::unique_ptr<IVectorFactory<T>> vectorFactory):
                _vectorFactory(std::move(vectorFactory)) {}

        VECTOR_POINTER createAndFillVector(const size_t size) noexcept override {
            std::cout << "createAndFillVector wurde mit Size " << size << " aufgerufen" << std::endl;
            return  _vectorFactory->createAndFillVector(size);

        }

    private:
        std::unique_ptr<IVectorFactory<T>> _vectorFactory;

    };

}
