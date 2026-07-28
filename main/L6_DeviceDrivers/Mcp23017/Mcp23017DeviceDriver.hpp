#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>

class I2cDeviceDriver;

typedef void (*InterruptFunctionPointer)(void*);

class Mcp23017DeviceDriver : public DeviceDriver
{
public:
    Mcp23017DeviceDriver();
    ~Mcp23017DeviceDriver();

    void SetI2cDeviceDriver(I2cDeviceDriver& i2cDeviceDriver);
    void SetInterruptConfiguration(bool enableInterrupt, uint8_t interruptPin);
    virtual bool HasInterruptTriggered() const = 0;
    virtual uint16_t ReadLastInterrupGpioStates() = 0;
    void Initialize() override;

    void ReadFromDriver();
    void WriteToDriver();
    
protected:
    virtual void SendInputPinsMask() = 0;
    virtual void InitializeInterrupts() = 0;

    bool IsInterruptEnabled() const;
    uint8_t GetInterruptPin() const;
    
    I2cDeviceDriver& GetI2cDeviceDriver();
    uint8_t GetI2cAddress();

    virtual void WriteGpio(uint16_t gpioStates) = 0;

private:
    I2cDeviceDriver* _i2cDeviceDriver;     
    uint8_t _i2cAddress;
    bool _enableInterrupt;
    uint8_t _interruptPin;
};

