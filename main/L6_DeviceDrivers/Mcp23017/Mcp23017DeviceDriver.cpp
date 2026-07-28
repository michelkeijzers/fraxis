#include "Mcp23017DeviceDriver.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"

Mcp23017DeviceDriver::Mcp23017DeviceDriver()
: _i2cDeviceDriver(nullptr), _i2cAddress(0), _enableInterrupt(false), _interruptPin(0)
{
}

Mcp23017DeviceDriver::~Mcp23017DeviceDriver()
{
}

void Mcp23017DeviceDriver::Initialize()
{
    SendInputPinsMask();
    if (_enableInterrupt)
    {
        InitializeInterrupts();
    }
}

bool Mcp23017DeviceDriver::IsInterruptEnabled() const
{
    return _enableInterrupt;
}

uint8_t Mcp23017DeviceDriver::GetInterruptPin() const
{
    return _interruptPin;
}

void Mcp23017DeviceDriver::SetInterruptConfiguration(bool enableInterrupt, uint8_t interruptPin)
{
    _enableInterrupt = enableInterrupt;
    _interruptPin = interruptPin;
}

void Mcp23017DeviceDriver::SetI2cDeviceDriver(I2cDeviceDriver& i2cDeviceDriver)
{
    _i2cDeviceDriver = &i2cDeviceDriver; 
}

I2cDeviceDriver& Mcp23017DeviceDriver::GetI2cDeviceDriver() 
{
    return *_i2cDeviceDriver; 
}

uint8_t Mcp23017DeviceDriver::GetI2cAddress() 
{
    return _i2cAddress; 
}

void Mcp23017DeviceDriver::WriteToDriver()
{
    auto* mcp23017DeviceModel = static_cast<Mcp23017DeviceModel*>(&GetDeviceModel());
    if (mcp23017DeviceModel->IsDirty())
    {
        uint16_t gpioStates = mcp23017DeviceModel->GetGpioStates();
        WriteGpio(gpioStates);
        mcp23017DeviceModel->ClearDirty();
    }
}
