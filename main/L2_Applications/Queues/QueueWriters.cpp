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
