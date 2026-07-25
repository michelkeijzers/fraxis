#pragma once

class OutputQueue;
class IoPins;
class Displays;

class OutputQueueReader
{
public:
    OutputQueueReader(OutputQueue& outputQueue, IoPins& ioPins, Displays& displays);
    ~OutputQueueReader();
    
    bool HandleMessage();

private:
    OutputQueue& _outputQueue;
    
    IoPins& _ioPins;
    Displays& _displays;
};
