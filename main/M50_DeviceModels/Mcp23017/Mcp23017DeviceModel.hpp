#pragma once

#include "../DeviceModel.hpp"
#include <list>
#include <cstdint>

class Mcp23017DeviceModel : public DeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Mcp23017DeviceModel();

    Mcp23017DeviceModel(const Mcp23017DeviceModel&) = delete;
    Mcp23017DeviceModel& operator=(const Mcp23017DeviceModel&) = delete;
    Mcp23017DeviceModel(Mcp23017DeviceModel&&) = delete;
    Mcp23017DeviceModel& operator=(Mcp23017DeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~Mcp23017DeviceModel() override;

    [[nodiscard]] uint8_t GetI2cAddress() const;
    void SetI2cAddress(
        uint8_t i2cAddress);
    void SetInputBits(
        std::list<uint8_t>& inputBits);
    void Initialize() override;

    [[nodiscard]] uint16_t GetInputPinsMask() const;
    [[nodiscard]] uint16_t GetGpioStates() const;
    void SetGpioStates(
        uint16_t gpioStates);

    [[nodiscard]] bool GetInputBit(
        uint8_t bit) const;
    void SetOutputBit(
        uint8_t bit, 
        bool state);

private:
    uint8_t _i2cAddress;
    uint16_t _inputPinsMask;
    uint16_t _gpioStates;
};
