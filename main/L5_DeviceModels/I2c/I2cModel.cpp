#include "I2cModel.hpp"
#include "../DeviceSettings.hpp"

I2cModel::I2cModel()
{
}

I2cModel::~I2cModel()
{
}

void I2cModel::Initialize()
{
    _clkPin = DeviceSettings::PIN_I2C_SCL;
    _sdaPin = DeviceSettings::PIN_I2C_SDA;
}

uint8_t I2cModel::GetClkPin() const 
{
    return _clkPin; }

uint8_t I2cModel::GetSdaPin() const
{
    return _sdaPin; 
}
