#pragma once

#include <cstdint>

namespace M50::I2c
{
    class IMcp23017DeviceModel;
}

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

        virtual void SetMcp23017DeviceModel(
            M50::I2c::IMcp23017DeviceModel& mcp23017DeviceModel) = 0;

        virtual M50::I2c::IMcp23017DeviceModel& GetMcp23017DeviceModel() = 0;

        virtual I2c::II2cDeviceDriver& GetI2cDeviceDriver() = 0;
        
        [[nodiscard]] virtual bool HasInterruptTriggered() const = 0;
        
        virtual uint16_t ReadLastInterrupGpioStates() = 0;

        virtual void WriteToDriver() = 0;
    };
}
