#pragma once

#include "../../M40_DomainModels/SevenSegmentsDisplays/SevenSegmentsDisplaysQueueReader.hpp"
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

namespace M60::SevenSegmentsDisplays
{
    class Tm1637DeviceDriver;
    class SevenSegmentsDisplaysInputQueueWriter;

    class SevenSegmentsDisplaysTaskDeviceDriversDelegate
    {
    public:
        static constexpr uint32_t MCP23017_WRITE_GPIOS_FREQUENCY = 100; // Hz

        static constexpr uint32_t LCD2004_WRITE_DISPLAY_FREQUENCY = 5; // Hz

        /// @brief The TM1637 displays are updated in alternating loops, meaning the actual maximum 
        /// frequency is 180 / 3 = 60 Hz
        static constexpr uint32_t TM1637_WRITE_DISPLAY_FREQUENCY = 180; // Hz

        explicit SevenSegmentsDisplaysTaskDeviceDriversDelegate(
            Context& context,
            Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
            Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
            Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
            M90::Assert::IAssert& assert,
            M90::Time::ITimeUtilities& timeUtilities);

        SevenSegmentsDisplaysTaskDeviceDriversDelegate(
            const SevenSegmentsDisplaysTaskDeviceDriversDelegate&) = delete;
        
        SevenSegmentsDisplaysTaskDeviceDriversDelegate& operator=(
            const SevenSegmentsDisplaysTaskDeviceDriversDelegate&) = delete;
        
        SevenSegmentsDisplaysTaskDeviceDriversDelegate(
            SevenSegmentsDisplaysTaskDeviceDriversDelegate&&) = delete;
        
        SevenSegmentsDisplaysTaskDeviceDriversDelegate& operator=(
            SevenSegmentsDisplaysTaskDeviceDriversDelegate&&) = delete;

        ~SevenSegmentsDisplaysTaskDeviceDriversDelegate() = default;

        void Initialize();

        void Run();

    private:
        Tm1637DeviceDriver& _tm1637DeviceDriverCentralPanel;

        Tm1637DeviceDriver& _tm1637DeviceDriverPlayer1;

        Tm1637DeviceDriver& _tm1637DeviceDriverPlayer2;

        Tm1637DeviceDriver& GetTm1637DeviceDriverId(
            Types::ETm1637Id tm1637id);

        Context& _context;

        M90::Assert::IAssert& _assert;

        M90::Time::ITimeUtilities& _timeUtilities;

        std::chrono::microseconds _lastTm1637WriteUs;

        Types::ETm1637Id _nextTm1637IdToUpdate;
    };
}
