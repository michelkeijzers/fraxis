#pragma once

#include "../DeviceModel.hpp"
#include "../../L9_Utils/Dirty/IDirty.hpp"
#include <cstdint>

class I2cModel;

class Mcp23017Model : public DeviceModel, public IDirty
{
public:
    Mcp23017Model();
    ~Mcp23017Model();

    void SetI2cModel(I2cModel& i2cModel);
    void Initialize() override;

private:
    I2cModel* _i2cModel;
    uint8_t _i2cAddress;
};
