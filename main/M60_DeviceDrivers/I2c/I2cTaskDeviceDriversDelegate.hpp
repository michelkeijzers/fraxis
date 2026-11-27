#pragma once

#include "../TaskDeviceDriversDelegate.hpp"
#include "../../M40_DomainModels/I2c/I2cInputQueueWriter.hpp"
#include <cstdint>
#include <chrono>
      
class I2cInputQueueWriter;
class IoPins;

namespace M50::I2c
{
    class IMcp23017DeviceModel;
    class Mcp23017DeviceModel;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

namespace M90::String
{
    class IStringUtilities;
}

namespace M90::Time
{
    class ITimeUtilities;
}

namespace M60::I2c
{
    class ILcd2004DeviceDriver;
    class IMcp23017DeviceDriver;

    class I2cTaskDeviceDriversDelegate : public TaskDeviceDriversDelegate
    {
    public:
        static constexpr uint32_t MCP23017_WRITE_GPIOS_FREQUENCY = 100; // Hz

        static constexpr uint32_t LCD2004_WRITE_DISPLAY_FREQUENCY = 5; // Hz

        explicit I2cTaskDeviceDriversDelegate(
            I2cInputQueueWriter& inputQueueWriter,
            IoPins& ioPins,
            M50::I2c::IMcp23017DeviceModel& mcp23017DeviceModel,
            M60::I2c::ILcd2004DeviceDriver& lcd2004DeviceDriver,
            M60::I2c::IMcp23017DeviceDriver& mcp23017DeviceDriver,
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log,
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
        I2cInputQueueWriter& _i2cInputQueueWriter;

        IoPins& _ioPins;
            
        M50::I2c::IMcp23017DeviceModel& _mcp23017DeviceModel;

        M60::I2c::ILcd2004DeviceDriver& _lcd2004DeviceDriver;

        M60::I2c::IMcp23017DeviceDriver& _mcp23017DeviceDriver;

        M90::Assert::IAssert& _assert;

        M90::Time::ITimeUtilities& _timeUtilities;

        std::chrono::microseconds _lastMcpWriteUs;

        std::chrono::microseconds _lastLcdWriteUs;
    };
}
