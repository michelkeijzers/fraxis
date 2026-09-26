#include "QueueWriters.hpp"
#include "I2cOutputQueueWriter.hpp"
#include "SpiOutputQueueWriter.hpp"
#include "LedStripsQueueWriter.hpp"

QueueWriters::QueueWriters(
    I2cOutputQueueWriter& i2cOutputQueueWriter, 
    SpiOutputQueueWriter& spiOutputQueueWriter,
    LedStripsQueueWriter& ledStripsQueueWriter)
:   
    _i2cOutputQueueWriter(i2cOutputQueueWriter),
    _spiOutputQueueWriter(spiOutputQueueWriter),
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

SpiOutputQueueWriter& QueueWriters::GetSpiOutputQueueWriter()
{
    return _spiOutputQueueWriter;
}

LedStripsQueueWriter& QueueWriters::GetLedStripsQueueWriter() 
{
    return _ledStripsQueueWriter; 
}
