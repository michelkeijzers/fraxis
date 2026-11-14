#pragma once

#include "../../DeviceDriver.hpp"
#include <cstdint>

namespace M60::I2c
{
    class I2cDeviceDriver;
}

namespace M80::Gpio
{
    class IGpio;
}

class Mcp23017DeviceModel;

using InterruptFunctionPointer = void (*)(void*);

namespace M60::Mcp23017
{
    class Mcp23017DeviceDriver : public DeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        Mcp23017DeviceDriver();

        Mcp23017DeviceDriver(
            const Mcp23017DeviceDriver&) = delete;
        
        Mcp23017DeviceDriver& operator=(
            const Mcp23017DeviceDriver&) = delete;
        
        Mcp23017DeviceDriver(
            Mcp23017DeviceDriver&&) = delete;
        
        Mcp23017DeviceDriver& operator=(
            Mcp23017DeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~Mcp23017DeviceDriver() override;

        void SetGpio(
            M80::Gpio::IGpio& gpio);
        
        I2c::I2cDeviceDriver& GetI2cDeviceDriver();
        
        void SetI2cDeviceDriver(
            I2c::I2cDeviceDriver& i2cDeviceDriver);
        
        void SetInterruptConfiguration(
            bool enableInterrupt,
            uint8_t interruptPin);
        
        void Initialize() override;

        Mcp23017DeviceModel& GetMcp23017DeviceModel();

        [[nodiscard]] bool HasInterruptTriggered() const;
        
        static void SetInterruptTriggered();
        
        uint16_t ReadLastInterrupGpioStates();

        void WriteToDriver();

    private:
        [[nodiscard]] M80::Gpio::IGpio& GetGpio();

        void SendInputPinsMask();

        void InitializeInterrupts();
        
        void InitializeInterruptOnEsp(
            uint8_t interruptPin);
        
        void InitializeInterruptOnMcp23017();

        [[nodiscard]] uint8_t GetI2cAddress();

        void WriteGpios(
            uint16_t gpioStates);

        bool _enableInterrupt;
        
        uint8_t _interruptPin;

        M60::I2c::I2cDeviceDriver* _i2cDeviceDriver;
        
        M80::Gpio::IGpio* _gpio;
    };
}
