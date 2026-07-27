#include "QueueWriters.hpp"

#include "I2cOutputQueueWriter.hpp"
#include "LedStripsQueueWriter.hpp"

QueueWriters::QueueWriters(I2cOutputQueueWriter& i2cOutputQueueWriter, LedStripsQueueWriter& ledStripsQueueWriter)
:   _i2cOutputQueueWriter(i2cOutputQueueWriter),
    _ledStripsQueueWriter(ledStripsQueueWriter)
{
}

QueueWriters::~QueueWriters() 
{
}

I2cOutputQueueWriter& QueueWriters::GetI2cOutputQueueWriter() 
{
    return _i2cOutputQueueWriter; 
}

LedStripsQueueWriter& QueueWriters::GetLedStripsQueueWriter() 
{
    return _ledStripsQueueWriter; 
}
