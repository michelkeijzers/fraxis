#pragma once

#include <list>
#include <cstdint>

namespace M50::I2c
{
    class IMcp23017DeviceModel
    {
    public:
        virtual ~IMcp23017DeviceModel() = default;

        [[nodiscard]] uint8_t virtual GetI2cAddress() const = 0;

        virtual void SetI2cAddress(
            uint8_t i2cAddress) = 0;

        virtual void SetInputBits(
            std::list<uint8_t>& inputBits) = 0;

        [[nodiscard]] virtual uint16_t GetInputPinsMask() const = 0;

        [[nodiscard]] virtual uint16_t GetGpioStates() const = 0;

        virtual void SetGpioStates(
            uint16_t gpioStates) = 0;

        [[nodiscard]] virtual bool GetInputBit(
            uint8_t bit) const = 0;

        virtual void SetOutputBit(
            uint8_t bit,
            bool state) = 0;
    };
}
