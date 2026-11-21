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

namespace M90::Time
{
    class ITimeUtilities;
}

namespace M60::I2c
{
    class Lcd2004DeviceDriver;
    class Mcp23017DeviceDriver;

    class I2cTaskDeviceDriversDelegate
    {
    public:
        static constexpr uint32_t MCP23017_WRITE_GPIOS_FREQUENCY = 100; // Hz

        static constexpr uint32_t LCD2004_WRITE_DISPLAY_FREQUENCY = 5; // Hz

        explicit I2cTaskDeviceDriversDelegate(
            Context& context,
            M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver,
            M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver,
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities,
            M90::Time::ITimeUtilities& timeUtilities);

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

        Context& _context;

        M90::Assert::IAssert& _assert;

        M90::Time::ITimeUtilities& _timeUtilities;

        I2cInputQueueWriter _i2cInputQueueWriter;

        std::chrono::microseconds _lastMcpWriteUs;

        std::chrono::microseconds _lastLcdWriteUs;
    };
}
