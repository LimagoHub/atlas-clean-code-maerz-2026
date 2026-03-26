//
// Created by JoachimWagner on 10.04.2024.
//

#pragma once
#include "Generator.h"
namespace atlas::generator {
    class IntGenerator : public Generator<int>{
    public:
        ~IntGenerator() override = default;
    };
}

