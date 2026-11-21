#pragma once

#include "../../M30_Messages/Types.hpp"
#include "../../M30_Messages/QueueProcessor.hpp"

class SevenSegmentsDisplaysQueue;
class Tm1637;

class SevenSegmentsDisplaysQueueReader : public QueueProcessor
{
public:
    SevenSegmentsDisplaysQueueReader(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities,
        SevenSegmentsDisplaysQueue& sevenSegmentsDisplaysQueue,  
        Tm1637& tm1637CentralPanel,
        Tm1637& tm1637Player1, 
        Tm1637& tm1637Player2);

    SevenSegmentsDisplaysQueueReader(
        const SevenSegmentsDisplaysQueueReader&) = delete;
    
    SevenSegmentsDisplaysQueueReader& operator=(
        const SevenSegmentsDisplaysQueueReader&) = delete;
    
    SevenSegmentsDisplaysQueueReader(
        SevenSegmentsDisplaysQueueReader&&) = delete;
    
    SevenSegmentsDisplaysQueueReader& operator=(
        SevenSegmentsDisplaysQueueReader&&) = delete;

    ~SevenSegmentsDisplaysQueueReader() override = default;
    
    bool HandleMessage();

private:
    SevenSegmentsDisplaysQueue& GetSevenSegmentsDisplaysQueue();
    
    Tm1637& GetTm1637ById(
        Types::ETm1637Id tm1637Id);

    Tm1637& _tm1637CentralPanel;
    
    Tm1637& _tm1637Player1;
    
    Tm1637& _tm1637Player2;
};
