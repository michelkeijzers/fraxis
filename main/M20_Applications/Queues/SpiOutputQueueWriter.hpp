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
        SpiOutputQueue& spiOutputQueue, 
        ApplicationsManager& applicationsManager);

    ~SpiOutputQueueWriter() = default;
    


    void SendReadFile(
        std::string fileName);

    void SendSaveFile(
        std::string fileName);

    

private:
    SpiOutputQueue& GetSpiOutputQueue();

    ApplicationsManager& _applicationsManager;  
};
