#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>

class Gpio;
class I2cDeviceDriver;
class Mcp23017DeviceModel;

using InterruptFunctionPointer = void (*)(void*);

class Mcp23017DeviceDriver : public DeviceDriver
{
public:
    Mcp23017DeviceDriver();
    ~Mcp23017DeviceDriver() = default;

    void SetGpio(
        Gpio& gpio);
    I2cDeviceDriver& GetI2cDeviceDriver();
    void SetI2cDeviceDriver(
        I2cDeviceDriver& i2cDeviceDriver);
    void SetInterruptConfiguration(
        bool enableInterrupt, 
        uint8_t interruptPin);
    void Initialize() override;

    Mcp23017DeviceModel& GetMcp23017DeviceModel();
    
    bool HasInterruptTriggered() const;
    static void SetInterruptTriggered();
    uint16_t ReadLastInterrupGpioStates();

    void WriteToDriver();
    
private:
    Gpio& GetGpio();
    void SendInputPinsMask();
    void InitializeInterrupts();
    void InitializeInterruptOnEsp(
        uint8_t interruptPin);
    void InitializeInterruptOnMcp23017(); 

    uint8_t GetI2cAddress();

    void WriteGpios(
        uint16_t gpioStates);

    bool _enableInterrupt;
    uint8_t _interruptPin;

    I2cDeviceDriver* _i2cDeviceDriver;     
    Gpio* _gpio;
};
