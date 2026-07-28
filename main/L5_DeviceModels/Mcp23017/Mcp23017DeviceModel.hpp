#pragma once

#include "../DeviceModel.hpp"
#include "../../L9_Utilities/Dirty/IDirty.hpp"
#include <list>
#include <cstdint>

class Mcp23017DeviceModel : public DeviceModel, public IDirty
{
public:
    Mcp23017DeviceModel();
    ~Mcp23017DeviceModel();

    uint8_t GetI2cAddress() const;
    void SetI2cAddress(uint8_t i2cAddress);
    void SetInputBits(std::list<uint8_t> inputBits);
    void Initialize() override;

    uint16_t GetInputPinsMask() const;
    uint16_t GetGpioStates() const;
    void SetGpioStates(uint16_t gpioStates);

    bool GetInputBit(uint8_t bit) const;
    void SetOutputBit(uint8_t bit, bool state);

private:
    uint8_t _i2cAddress;
    uint16_t _inputPinsMask;
    uint16_t _gpioStates;
};
