#pragma once

#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../../M30_Messages/Types.hpp"

#include <cstdint>

class Context;

namespace M60::PassiveBuzzer
{
    class PassiveBuzzerTaskDeviceDriversDelegate
    {
    public:
        explicit PassiveBuzzerTaskDeviceDriversDelegate(
            Context& context);

        PassiveBuzzerTaskDeviceDriversDelegate(
            const PassiveBuzzerTaskDeviceDriversDelegate&) = delete;

        PassiveBuzzerTaskDeviceDriversDelegate& operator=(
            const PassiveBuzzerTaskDeviceDriversDelegate&) = delete;
        
        PassiveBuzzerTaskDeviceDriversDelegate(
            PassiveBuzzerTaskDeviceDriversDelegate&&) = delete;
        
        PassiveBuzzerTaskDeviceDriversDelegate& operator=(
            PassiveBuzzerTaskDeviceDriversDelegate&&) = delete;

        ~PassiveBuzzerTaskDeviceDriversDelegate() = default;

        void Initialize();

        void Run();

    private:
        Context& _context;
    };
}
