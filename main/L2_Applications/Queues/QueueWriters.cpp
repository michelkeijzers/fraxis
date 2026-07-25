#include "QueueWriters.hpp"

#include "OutputQueueWriter.hpp"
#include "LedStripsQueueWriter.hpp"

QueueWriters::QueueWriters(OutputQueueWriter& outputQueueWriter, LedStripsQueueWriter& ledStripsQueueWriter)
:   _outputQueueWriter(outputQueueWriter),
    _ledStripsQueueWriter(ledStripsQueueWriter)
{
}

QueueWriters::~QueueWriters() 
{
}

OutputQueueWriter& QueueWriters::GetOutputQueueWriter() 
{
    return _outputQueueWriter; 
}

LedStripsQueueWriter& QueueWriters::GetLedStripsQueueWriter() 
{
    return _ledStripsQueueWriter; 
}
