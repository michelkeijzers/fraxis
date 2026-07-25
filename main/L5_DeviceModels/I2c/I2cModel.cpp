#include "I2cModel.hpp"

I2cModel::I2cModel()
{
}

I2cModel::~I2cModel()
{
}

uint8_t I2cModel::GetClkPin() const 
{
    return _clkPin; }

uint8_t I2cModel::GetSdaPin() const
{
    return _sdaPin; 
}


void I2cModel::SetClkPin(uint8_t pin) 
{
    _clkPin = pin; 
}

void I2cModel::SetSdaPin(uint8_t pin) 
{
    _sdaPin = pin; 
}
