#include "Mcp23017DeviceDriver.hpp"
#include "Mcp23017InterruptHandler.hpp"
#include "Mcp23017Registers.hpp"
#include "../../../M50_DeviceModels/IDeviceModel.hpp"
#include "../../I2c/I2cDeviceDriver.hpp"
#include "../../../M50_DeviceModels/I2c/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../../M80_Services/Gpio/Gpio.hpp"
#include "../../../M90_Utilities/Assert/IAssert.hpp"

#ifdef ESP_PLATFORM
    #include "esp_attr.h"
#else // Windows
    #define IRAM_ATTR 
#endif // ESP_PLATFORM

namespace M60::I2c
{
    volatile static bool g_mcpInterruptTriggered = false; // NOSONAR: not const

    Mcp23017DeviceDriver::Mcp23017DeviceDriver(
        II2cDeviceDriver& i2cDeviceDriver,
        bool enableInterrupt,
        uint8_t interruptPin,
        M80::Gpio::IGpio& gpio,
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities)
    :
        DeviceDriver(assert, stringUtilities),
        _enableInterrupt(enableInterrupt),
        _interruptPin(interruptPin),
        _i2cDeviceDriver(i2cDeviceDriver),
        _gpio(gpio)
    {
        // No functionality required.
    }

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Mcp23017DeviceDriver::~Mcp23017DeviceDriver() = default;

    void Mcp23017DeviceDriver::SetMcp23017DeviceModel(
        M50::I2c::IMcp23017DeviceModel& mcp23017DeviceModel)
    {
        _mcp23017DeviceModel = &mcp23017DeviceModel;
    }

    M50::I2c::IMcp23017DeviceModel& Mcp23017DeviceDriver::GetMcp23017DeviceModel()
    {
        return *_mcp23017DeviceModel;
    }

    uint8_t Mcp23017DeviceDriver::GetI2cAddress()
    {
        return GetMcp23017DeviceModel().GetI2cAddress();
    }

    I2c::II2cDeviceDriver& Mcp23017DeviceDriver::GetI2cDeviceDriver()
    {
        return _i2cDeviceDriver;
    }

    void Mcp23017DeviceDriver::SendInputPinsMask()
    {
        M50::I2c::IMcp23017DeviceModel& mcp23017DeviceModel = GetMcp23017DeviceModel();
        uint16_t inputPinsMask = mcp23017DeviceModel.GetInputPinsMask();

        auto directionPortA = static_cast<uint8_t>(inputPinsMask >> 8);
        auto directionPortB = static_cast<uint8_t>(inputPinsMask & 0xFF);

        auto& deviceDriver = GetI2cDeviceDriver();
        deviceDriver.WriteRegister(
            mcp23017DeviceModel.GetI2cAddress(), MCP23017_IODIRA, &directionPortA, 1);
        deviceDriver.WriteRegister(
            mcp23017DeviceModel.GetI2cAddress(), MCP23017_IODIRB, &directionPortB, 1);
    }

    void Mcp23017DeviceDriver::Initialize()
    {
        SendInputPinsMask();
        if (_enableInterrupt)
        {
            InitializeInterrupts();
        }
    }

    void Mcp23017DeviceDriver::InitializeInterrupts()
    {
        InitializeInterruptOnEsp(_interruptPin);
        InitializeInterruptOnMcp23017();
    }

    void Mcp23017DeviceDriver::InitializeInterruptOnEsp(
        uint8_t interruptPin)
    {
        GetGpio().ConfigAsInterruptInput(interruptPin);
        GetGpio().InstallIsrService();
        GetGpio().AddMcp23017InterruptHandler(interruptPin, Mcp23017InterruptHandler, nullptr);
    }

    void Mcp23017DeviceDriver::InitializeInterruptOnMcp23017()
    {
        auto& deviceDriver = GetI2cDeviceDriver();
        const auto& mcp23017DeviceModel = GetMcp23017DeviceModel();
        uint16_t inputPinsMask = mcp23017DeviceModel.GetInputPinsMask();

        deviceDriver.WriteRegister(
            MCP23017_GPINTENA,
            static_cast<uint8_t>(inputPinsMask >> 8),
            1); // Port A
        deviceDriver.WriteRegister(
            MCP23017_GPINTENB,
            static_cast<uint8_t>(inputPinsMask & 0xFF),
            1); // Port B

        // Compare against previous value (default).
        deviceDriver.WriteRegister(MCP23017_INTCONA, 0x00, 1);
        deviceDriver.WriteRegister(MCP23017_INTCONB, 0x00, 1);

        // Clear interrupt flags.
        deviceDriver.ReadRegister(MCP23017_INTCAPA, 1);
        deviceDriver.ReadRegister(MCP23017_INTCAPB, 1);
    }

    M80::Gpio::IGpio& Mcp23017DeviceDriver::GetGpio()
    {
        return _gpio;
    }

    /// @brief Reads GPIO states from last interrupt.
    /// @details ReadRegister of INTCAPA/B does NOT reset output pins and leaves the actual output 
    /// state unchanged.
    /// @return 
    uint16_t Mcp23017DeviceDriver::ReadLastInterrupGpioStates()
    {
        GetAssert().IsTrue(
            Types::ETaskId::I2cTask, g_mcpInterruptTriggered, "Interrupt not triggered");
        g_mcpInterruptTriggered = false;

        auto& deviceDriver = GetI2cDeviceDriver();
        uint8_t i2cAddress = GetI2cAddress();
        uint8_t capA = deviceDriver.ReadRegister(i2cAddress, MCP23017_INTCAPA);
        uint8_t capB = deviceDriver.ReadRegister(i2cAddress, MCP23017_INTCAPB);
        auto combined = static_cast<uint16_t>(
            (static_cast<uint16_t>(capA) << 8) | static_cast<uint16_t>(capB));
        return combined;
    }

    bool Mcp23017DeviceDriver::HasInterruptTriggered() const
    {
        return g_mcpInterruptTriggered;
    }

    /// @brief Sets interrupt triggered flag. This is the interrupt handler for the MCP23017 interrupt 
    /// pin.
    /* static */ void Mcp23017DeviceDriver::SetInterruptTriggered()
    {
        g_mcpInterruptTriggered = true;
    }

    void Mcp23017DeviceDriver::WriteToDriver()
    {
        if (GetDeviceModel().IsDirty())
        {
            const auto& mcp23017DeviceModel = GetMcp23017DeviceModel();
            uint16_t gpioStates = mcp23017DeviceModel.GetGpioStates();
            WriteGpios(gpioStates);
            GetDeviceModel().ClearDirty();
        }
    }

    void Mcp23017DeviceDriver::WriteGpios(
        uint16_t gpioStates)
    {
        auto portA = static_cast<uint8_t>((gpioStates >> 8) & 0xFF);
        auto portB = static_cast<uint8_t>(gpioStates & 0xFF);

        auto& deviceDriver = GetI2cDeviceDriver();
        uint8_t i2cAddress = GetI2cAddress();
        deviceDriver.WriteRegister(i2cAddress, MCP23017_OLATA, &portA, 1);
        deviceDriver.WriteRegister(i2cAddress, MCP23017_OLATB, &portB, 1);
    }
}
