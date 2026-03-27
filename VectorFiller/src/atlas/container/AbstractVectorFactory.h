//
// Created by JoachimWagner on 10.04.2024.
//

#pragma once
#include "IVectorFactory.h"

namespace atlas::container {

    template<class T>
    class AbstractVectorFactory : public IVectorFactory<T> {
        using VectorPtr = std::shared_ptr<std::vector<T>>;

    public:
        ~AbstractVectorFactory() override = default;

        auto createAndFillVector(size_t size) -> VectorPtr final {
            auto data = std::make_shared<std::vector<T>>(size);
            fillVector(data);
            return data;
        }

    protected:
        AbstractVectorFactory() = default;
        virtual auto fillVector(VectorPtr data) const noexcept -> void = 0;
    };

} // namespace atlas::container
