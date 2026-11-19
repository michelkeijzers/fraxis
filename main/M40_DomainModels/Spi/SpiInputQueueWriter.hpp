#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/Spi/SpiInputQueue.hpp"
#include <cstdint>
#include <string>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

class spiInputQueue;
class MicroSdCard;

class SpiInputQueueWriter : public QueueProcessor
{
public:
    SpiInputQueueWriter(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        SpiInputQueue& spiInputQueue,
        MicroSdCard& microSdCard);

    SpiInputQueueWriter(
        const SpiInputQueueWriter&) = delete;

    SpiInputQueueWriter& operator=(
        const SpiInputQueueWriter&) = delete;

    SpiInputQueueWriter(
        SpiInputQueueWriter&&) = delete;

    SpiInputQueueWriter& operator=(
        SpiInputQueueWriter&&) = delete;

    ~SpiInputQueueWriter() override = default;

    // NOSONAR TODO void SendLoadedDataMessage();

    void SendWrite();

private:
    SpiInputQueue& GetSpiInputQueue();

    MicroSdCard& _microSdCard;

    M90::Log::ILog& _log;
};
