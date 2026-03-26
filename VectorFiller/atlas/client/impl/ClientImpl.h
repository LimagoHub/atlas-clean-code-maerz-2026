//
// Created by JoachimWagner on 10.04.2024.
//
#include <vector>
#include <memory>
#include <iostream>
#include "../IClient.h"
#include "../../container/IVectorFactory.h"

namespace atlas::client {

    class VectorClientImpl: public IClient {
        using VECTOR = std::unique_ptr<atlas::container::IVectorFactory<int> >;

        VECTOR factory;


    public:

        explicit VectorClientImpl(VECTOR factory) : factory(std::move(factory)) {}

        ~VectorClientImpl() override = default;

        auto processVector() noexcept ->void  override{

            auto v = factory->createAndFillVector(INT32_MAX / 2);
            for (int i = 0; i < 3; ++i) {
                std::cout << v->at(i) << std::endl;
            }
        }
    };

}
