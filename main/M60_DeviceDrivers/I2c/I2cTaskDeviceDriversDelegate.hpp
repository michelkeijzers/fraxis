#pragma once

#include "../../M40_DomainModels/I2c/I2cInputQueueWriter.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <chrono>

class Context;

namespace M90::Assert
{
    class IAssert;
}

namespace M60::I2c
{
    class Lcd2004DeviceDriver;
    class Mcp23017DeviceDriver;
    class Tm1637DeviceDriver;

    class I2cTaskDeviceDriversDelegate
    {
    public:
        static constexpr uint32_t MCP23017_WRITE_GPIOS_FREQUENCY = 100; // Hz

        static constexpr uint32_t LCD2004_WRITE_DISPLAY_FREQUENCY = 5; // Hz

        /// @brief The TM1637 displays are updated in alternating loops, meaning the actual maximum 
        /// frequency is 180 / 3 = 60 Hz
        static constexpr uint32_t TM1637_WRITE_DISPLAY_FREQUENCY = 180; // Hz

        explicit I2cTaskDeviceDriversDelegate(
            Context& context,
            M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver,
            M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver,
            M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
            M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
            M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

        I2cTaskDeviceDriversDelegate(
            const I2cTaskDeviceDriversDelegate&) = delete;
        
        I2cTaskDeviceDriversDelegate& operator=(
            const I2cTaskDeviceDriversDelegate&) = delete;
        
        I2cTaskDeviceDriversDelegate(
            I2cTaskDeviceDriversDelegate&&) = delete;
        
        I2cTaskDeviceDriversDelegate& operator=(
            I2cTaskDeviceDriversDelegate&&) = delete;

        ~I2cTaskDeviceDriversDelegate() = default;

        void Initialize();

        void Run();

    private:
        M60::I2c::Lcd2004DeviceDriver& _lcd2004DeviceDriver;

        M60::I2c::Mcp23017DeviceDriver& _mcp23017DeviceDriver;

        M60::I2c::Tm1637DeviceDriver& _tm1637DeviceDriverCentralPanel;

        M60::I2c::Tm1637DeviceDriver& _tm1637DeviceDriverPlayer1;

        M60::I2c::Tm1637DeviceDriver& _tm1637DeviceDriverPlayer2;

        Tm1637DeviceDriver& GetTm1637DeviceDriverId(
            Types::ETm1637Id tm1637id);

        Context& _context;

        M90::Assert::IAssert& _assert;

        I2cInputQueueWriter _i2cInputQueueWriter;

        std::chrono::microseconds _lastMcpWriteUs;

        std::chrono::microseconds _lastLcdWriteUs;

        std::chrono::microseconds _lastTm1637WriteUs;

        Types::ETm1637Id _nextTm1637IdToUpdate;
    };
}
