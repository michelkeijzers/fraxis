#pragma once

#include "IMcp23017DeviceModel.hpp"
#include "../../DeviceModel.hpp"
#include <list>
#include <cstdint>

namespace M50::I2c
{
    class Mcp23017DeviceModel : public DeviceModel, public IMcp23017DeviceModel
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        Mcp23017DeviceModel(
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log,
            M90::String::IStringUtilities& stringUtilities);

        Mcp23017DeviceModel(
            const Mcp23017DeviceModel&) = delete;

        Mcp23017DeviceModel& operator=(
            const Mcp23017DeviceModel&) = delete;

        Mcp23017DeviceModel(
            Mcp23017DeviceModel&&) = delete;

        Mcp23017DeviceModel& operator=(
            Mcp23017DeviceModel&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~Mcp23017DeviceModel() override;

        [[nodiscard]] uint8_t GetI2cAddress() const override;

        void SetI2cAddress(
            uint8_t i2cAddress) override;

        void SetInputBits(
            std::list<uint8_t>& inputBits) override;

        void Initialize() override;

        [[nodiscard]] uint16_t GetInputPinsMask() const override;

        [[nodiscard]] uint16_t GetGpioStates() const override;

        void SetGpioStates(
            uint16_t gpioStates) override;

        [[nodiscard]] bool GetInputBit(
            uint8_t bit) const override;

        void SetOutputBit(
            uint8_t bit,
            bool state) override;

    private:
        uint8_t _i2cAddress;

        uint16_t _inputPinsMask;

        uint16_t _gpioStates;
    };
}
