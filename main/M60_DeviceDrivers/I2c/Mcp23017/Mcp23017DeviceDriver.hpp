#pragma once

#include "IMcp23017DeviceDriver.hpp"
#include "../../DeviceDriver.hpp"
#include <cstdint>

namespace M80::Gpio
{
    class IGpio;
}

class Mcp23017DeviceModel;

namespace M90::String
{
    class IStringUtilities;
}

namespace M90::Time
{
    class ITimeUtilities;
}


using InterruptFunctionPointer = void (*)(void*);

namespace M60::I2c
{
    class II2cDeviceDriver;

    class Mcp23017DeviceDriver : public DeviceDriver, public IMcp23017DeviceDriver
    {
    public:
        Mcp23017DeviceDriver(
            I2c::II2cDeviceDriver& i2cDeviceDriver,
            bool enableInterrupt,
            uint8_t interruptPin,
            M80::Gpio::IGpio& gpio,
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

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

        II2cDeviceDriver& GetI2cDeviceDriver() override;
        
        void Initialize() override;

        Mcp23017DeviceModel& GetMcp23017DeviceModel() override;

        [[nodiscard]] bool HasInterruptTriggered() const override;
        
        /// @remarks static method cannot be overridden.
        static void SetInterruptTriggered();
        
        uint16_t ReadLastInterrupGpioStates() override;

        void WriteToDriver() override;

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

        M60::I2c::II2cDeviceDriver& _i2cDeviceDriver;
        
        M80::Gpio::IGpio& _gpio;
    };
}
