#pragma once

#include <cstdint>

class Mcp23017DeviceModel;

namespace M80::Gpio
{
    class IGpio;
}

using InterruptFunctionPointer = void (*)(void*);

namespace M60::I2c
{
    class II2cDeviceDriver;

    class IMcp23017DeviceDriver
    {
    public:
        virtual ~IMcp23017DeviceDriver() = default;

        virtual I2c::II2cDeviceDriver& GetI2cDeviceDriver() = 0;
        
        virtual Mcp23017DeviceModel& GetMcp23017DeviceModel() = 0;

        [[nodiscard]] virtual bool HasInterruptTriggered() const = 0;
        
        virtual uint16_t ReadLastInterrupGpioStates() = 0;

        virtual void WriteToDriver() = 0;
    };
}
