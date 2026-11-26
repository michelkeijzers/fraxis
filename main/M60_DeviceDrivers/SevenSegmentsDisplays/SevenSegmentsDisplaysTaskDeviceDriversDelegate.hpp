#pragma once

#include "../TaskDeviceDriversDelegate.hpp"
#include "../../M40_DomainModels/SevenSegmentsDisplays/SevenSegmentsDisplaysQueueReader.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <chrono>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

namespace M90::Time
{
    class ITimeUtilities;
}

namespace M60::SevenSegmentsDisplays
{
    class ITm1637DeviceDriver;
    class SevenSegmentsDisplaysInputQueueWriter;

    class SevenSegmentsDisplaysTaskDeviceDriversDelegate : public TaskDeviceDriversDelegate
    {
    public:
        static constexpr uint32_t MCP23017_WRITE_GPIOS_FREQUENCY = 100; // Hz

        static constexpr uint32_t LCD2004_WRITE_DISPLAY_FREQUENCY = 5; // Hz

        /// @brief The TM1637 displays are updated in alternating loops, meaning the actual maximum 
        /// frequency is 180 / 3 = 60 Hz
        static constexpr uint32_t TM1637_WRITE_DISPLAY_FREQUENCY = 180; // Hz

        SevenSegmentsDisplaysTaskDeviceDriversDelegate(
            ITm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
            ITm1637DeviceDriver& tm1637DeviceDriverPlayer1,
            ITm1637DeviceDriver& tm1637DeviceDriverPlayer2,
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log,
            M90::Time::ITimeUtilities& timeUtilities);

        SevenSegmentsDisplaysTaskDeviceDriversDelegate(
            const SevenSegmentsDisplaysTaskDeviceDriversDelegate&) = default;
        
        SevenSegmentsDisplaysTaskDeviceDriversDelegate& operator=(
            const SevenSegmentsDisplaysTaskDeviceDriversDelegate&) = default;
        
        SevenSegmentsDisplaysTaskDeviceDriversDelegate(
            SevenSegmentsDisplaysTaskDeviceDriversDelegate&&) = default;
        
        SevenSegmentsDisplaysTaskDeviceDriversDelegate& operator=(
            SevenSegmentsDisplaysTaskDeviceDriversDelegate&&) = default;

        ~SevenSegmentsDisplaysTaskDeviceDriversDelegate() = default;

        void Initialize();

        void Run();

    private:
        ITm1637DeviceDriver& _tm1637DeviceDriverCentralPanel;

        ITm1637DeviceDriver& _tm1637DeviceDriverPlayer1;

        ITm1637DeviceDriver& _tm1637DeviceDriverPlayer2;

        ITm1637DeviceDriver& GetTm1637DeviceDriverId(
            Types::ETm1637Id tm1637id);

        M90::Assert::IAssert& _assert;

        M90::Time::ITimeUtilities& _timeUtilities;

        std::chrono::microseconds _lastTm1637WriteUs;

        Types::ETm1637Id _nextTm1637IdToUpdate;
    };
}
