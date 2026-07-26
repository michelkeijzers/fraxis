#pragma once

#include "../DeviceModel.hpp"
#include "../../L9_Utils/Dirty/IDirty.hpp"
#include <cstdint>

class Mcp23017Model : public DeviceModel, public IDirty
{
public:
    Mcp23017Model();
    ~Mcp23017Model();

    uint8_t GetI2cAddress() const;
    void SetI2cAddress(uint8_t i2cAddress);

    void Initialize() override;

private:
    uint8_t _i2cAddress;
};
