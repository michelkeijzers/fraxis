#pragma once

#include "../../M30_Messages/Types.hpp"

#include <cstdint>

class Context;

namespace M60::Ws28xx
{
    class Ws28xxTaskDeviceDriversDelegate
    {
    public:
        explicit Ws28xxTaskDeviceDriversDelegate(
            Context& context);

        Ws28xxTaskDeviceDriversDelegate(
            const Ws28xxTaskDeviceDriversDelegate&) = delete;

        Ws28xxTaskDeviceDriversDelegate& operator=(
            const Ws28xxTaskDeviceDriversDelegate&) = delete;

        Ws28xxTaskDeviceDriversDelegate(
            Ws28xxTaskDeviceDriversDelegate&&) = delete;

        Ws28xxTaskDeviceDriversDelegate& operator=(
            Ws28xxTaskDeviceDriversDelegate&&) = delete;

        ~Ws28xxTaskDeviceDriversDelegate() = default;

        void Initialize();

        void Run();

    private:
        Context& _context;
    };
}
