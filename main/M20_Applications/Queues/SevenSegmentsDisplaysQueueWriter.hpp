#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M40_DomainModels/SevenSegmentsDisplays/Tm1637.hpp"
#include "../../M60_DeviceDrivers/SevenSegmentsDisplays/Tm1637DeviceDriver.hpp"
#include <cstdint>
#include <string>
#include <array>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::String
{
    class IStringUtilities;
}

class SevenSegmentsDisplaysQueue;
class ApplicationsManager;

class SevenSegmentsDisplaysQueueWriter : public QueueProcessor
{
public:
    SevenSegmentsDisplaysQueueWriter(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        SevenSegmentsDisplaysQueue& i2cOutputQueue,
        ApplicationsManager& applicationsManager);

    SevenSegmentsDisplaysQueueWriter(
        const SevenSegmentsDisplaysQueueWriter&) = delete;
    
    SevenSegmentsDisplaysQueueWriter& operator=(
        const SevenSegmentsDisplaysQueueWriter&) = delete;
    
    SevenSegmentsDisplaysQueueWriter(
        SevenSegmentsDisplaysQueueWriter&&) = delete;
    
    SevenSegmentsDisplaysQueueWriter& operator=(
        SevenSegmentsDisplaysQueueWriter&&) = delete;

    ~SevenSegmentsDisplaysQueueWriter() override = default;
    
    void SendTm1637Enable(
        Types::ETm1637Id tm1637Id,
        bool enable);

    void SendTm1637Brightness(
        Types::ETm1637Id tm1637Id, 
        uint8_t brightness);

    void SendTm1637Value(
        Types::ETm1637Id tm1637Id, 
        uint32_t value);
    
    void SendTm1637Time(
        Types::ETm1637Id tm1637Id,
        uint8_t first,
        uint8_t second);

private:
    SevenSegmentsDisplaysQueue& GetSevenSegmentsDisplaysQueue();

    ApplicationsManager& _applicationsManager;
};
