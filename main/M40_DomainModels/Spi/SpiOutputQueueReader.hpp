#pragma once

#include "../../M30_Messages/Types.hpp"
#include "../../M30_Messages/QueueProcessor.hpp"

namespace M90::Assert
{
    class IAssert;
}

class SpiOutputQueue;
class MicroSdCard;

class SpiOutputQueueReader : public QueueProcessor
{
public:
    SpiOutputQueueReader(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities,
        SpiOutputQueue& spiOutputQueue,  
        MicroSdCard& microSdCard);

    SpiOutputQueueReader(
        const SpiOutputQueueReader&) = delete;
    
    SpiOutputQueueReader& operator=(
        const SpiOutputQueueReader&) = delete;
    
    SpiOutputQueueReader(
        SpiOutputQueueReader&&) = delete;
    
    SpiOutputQueueReader& operator=(
        SpiOutputQueueReader&&) = delete;

    ~SpiOutputQueueReader() override = default;
    
    bool HandleMessage();

private:
    SpiOutputQueue& GetSpiOutputQueue();

    MicroSdCard& _microSdCard;
};
