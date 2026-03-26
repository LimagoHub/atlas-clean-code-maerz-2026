//
// Created by JoachimWagner on 10.04.2024.
//

#pragma once

#pragma once
#include "VectorFactory.h"
namespace atlas::container {

    template<class T>
    class AbstractVectorFactory: public VectorFactory<T>{


        using VECTOR = std::shared_ptr<std::vector<T> >;



    public:

        ~AbstractVectorFactory() override = default;

        auto createAndFillVector(size_t size) noexcept-> VECTOR override final {
            auto data_ = std::make_shared<std::vector<T>>(size);

            fill_array(data_);
            return data_;
        }
    protected:
        AbstractVectorFactory() = default;
        virtual auto fill_array(VECTOR data) const -> void = 0;
    };

} // collections
