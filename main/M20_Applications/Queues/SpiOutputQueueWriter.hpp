#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <string>

class SpiOutputQueue;
class ApplicationsManager;

class SpiOutputQueueWriter : public QueueProcessor
{
public:
    SpiOutputQueueWriter(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        SpiOutputQueue& spiOutputQueue, 
        ApplicationsManager& applicationsManager);

    SpiOutputQueueWriter(
        const SpiOutputQueueWriter&) = delete;
    
    SpiOutputQueueWriter& operator=(
        const SpiOutputQueueWriter&) = delete;
    
    SpiOutputQueueWriter(
        SpiOutputQueueWriter&&) = delete;
    
    SpiOutputQueueWriter& operator=(
        SpiOutputQueueWriter&&) = delete;

    ~SpiOutputQueueWriter() override = default;

    //void SendReadFile( // NOSONAR VCR001: TODO SPI
    //    std::string fileName);

    //void SendSaveFile( // NOSONAR VCR001: TODO SPI
    //    std::string fileName);

private:
    SpiOutputQueue& GetSpiOutputQueue();

    ApplicationsManager& _applicationsManager;  
};
