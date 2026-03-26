//
// Created by JoachimWagner on 26.03.2026.
//

#pragma once

namespace atlas::client {
    class IClient {
    public:
        virtual ~IClient() = default;
        virtual auto processVector() noexcept -> void = 0;
    };
} // client