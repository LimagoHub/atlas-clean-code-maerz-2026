//
// Created by JoachimWagner on 20.01.2026.
//

#pragma once

#include <string>

namespace atlas::io {

    class Writer {
    public:
        virtual ~Writer() = default;
        virtual auto write(const std::string & message) const -> void = 0;
    };

} // io
