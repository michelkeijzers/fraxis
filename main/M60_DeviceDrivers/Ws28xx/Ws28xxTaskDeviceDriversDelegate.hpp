#pragma once

#include "../../M30_Messages/Types.hpp"

#include <cstdint>

class Context;

namespace M60
{
    namespace Ws28xx
    {
        class IWs28xxDeviceDriver;
    };
};

namespace M60::Ws28xx
{
    class Ws28xxTaskDeviceDriversDelegate
    {
    public:
        explicit Ws28xxTaskDeviceDriversDelegate(
            Context& context,
            M60::Ws28xx::IWs28xxDeviceDriver& ws28xxDeviceDriver);

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

        M60::Ws28xx::IWs28xxDeviceDriver& _ws28xxDeviceDriver;
    };
}
