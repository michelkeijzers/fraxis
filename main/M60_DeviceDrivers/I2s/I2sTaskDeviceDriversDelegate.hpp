#pragma once

#include "../../M40_DomainModels/I2s/I2sMicrophone/I2sMicrophone.hpp"
#include "../../M40_DomainModels/I2s/I2sDac/I2sDac.hpp"
#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../../M30_Messages/Types.hpp"

#include <cstdint>

class Context;

namespace M60::I2s
{
    class I2sTaskDeviceDriversDelegate
    {
    public:
        explicit I2sTaskDeviceDriversDelegate(
            Context& context);

        I2sTaskDeviceDriversDelegate(
            const I2sTaskDeviceDriversDelegate&) = delete;

        I2sTaskDeviceDriversDelegate& operator=(
            const I2sTaskDeviceDriversDelegate&) = delete;
        
        I2sTaskDeviceDriversDelegate(
            I2sTaskDeviceDriversDelegate&&) = delete;
        
        I2sTaskDeviceDriversDelegate& operator=(
            I2sTaskDeviceDriversDelegate&&) = delete;

        ~I2sTaskDeviceDriversDelegate() = default;

        void Initialize();

        void Run();

    private:
        Context& _context;
    };
}
