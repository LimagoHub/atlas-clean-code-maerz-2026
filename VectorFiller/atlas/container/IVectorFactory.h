//
// Created by JoachimWagner on 21.01.2026.
//

#pragma once

#include <vector>
#include <memory>

namespace atlas::container {
    template<class T>
    class IVectorFactory {
        using VECTOR_POINTER = std::shared_ptr<std::vector<T>>;
    public:
        virtual ~IVectorFactory() = default;
        [[nodiscard]] virtual auto createAndFillVector(const size_t size)  noexcept -> VECTOR_POINTER = 0;
    };

} // container
