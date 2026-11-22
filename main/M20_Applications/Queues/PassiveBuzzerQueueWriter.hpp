#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../../M60_DeviceDrivers/PassiveBuzzer/PassiveBuzzerDeviceDriver.hpp"
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

class PassiveBuzzerQueue;
class ApplicationsManager;

class PassiveBuzzerQueueWriter : public QueueProcessor
{
public:
    PassiveBuzzerQueueWriter(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        PassiveBuzzerQueue& passiveBuzzerQueue,
        ApplicationsManager& applicationsManager);

    PassiveBuzzerQueueWriter(
        const PassiveBuzzerQueueWriter&) = delete;

    PassiveBuzzerQueueWriter& operator=(
        const PassiveBuzzerQueueWriter&) = delete;

    PassiveBuzzerQueueWriter(
        PassiveBuzzerQueueWriter&&) = delete;

    PassiveBuzzerQueueWriter& operator=(
        PassiveBuzzerQueueWriter&&) = delete;

    ~PassiveBuzzerQueueWriter() override = default;

private:
    PassiveBuzzerQueue& GetPassiveBuzzerQueue();

    ApplicationsManager& _applicationsManager;
};
