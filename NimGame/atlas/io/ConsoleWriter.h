//
// Created by JoachimWagner on 20.01.2026.
//

#pragma once
#include <iostream>
#include "Writer.h"
namespace atlas::io {

    class ConsoleWriter :public Writer{
    public:
        ~ConsoleWriter() override = default;

        auto write(const std::string &message) const -> void override {
            std::cout << message << std::endl;
        }
    };

} // io
