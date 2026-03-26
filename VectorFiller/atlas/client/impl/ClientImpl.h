//
// Created by JoachimWagner on 10.04.2024.
//
#include <vector>
#include <memory>
#include <iostream>
#include "../Client.h"
#include "../../container/VectorFactory.h"

namespace atlas::client {

    class VectorClientImpl: public Client {
        using VECTOR = std::unique_ptr<atlas::container::VectorFactory<int> >;

        VECTOR factory;


    public:

        explicit VectorClientImpl(VECTOR factory) : factory(std::move(factory)) {}

        ~VectorClientImpl() override = default;

        auto doSomethingWithLargeContainer() noexcept ->void  override{

            auto v = factory->createAndFillVector(INT32_MAX / 2);
            for (int i = 0; i < 3; ++i) {
                std::cout << v->at(i) << std::endl;
            }
        }
    };

}
