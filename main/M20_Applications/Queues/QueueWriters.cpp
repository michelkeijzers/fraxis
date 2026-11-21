#include "QueueWriters.hpp"
#include "I2cOutputQueueWriter.hpp"
#include "I2sOutputQueueWriter.hpp"
#include "LedStripsQueueWriter.hpp"
#include "PassiveBuzzerQueueWriter.hpp"
#include "SevenSegmentsDisplaysQueueWriter.hpp"
#include "SpiOutputQueueWriter.hpp"

QueueWriters::QueueWriters(
    I2cOutputQueueWriter& i2cOutputQueueWriter, 
    I2sOutputQueueWriter& i2sOutputQueueWriter,
    LedStripsQueueWriter& ledStripsQueueWriter,
    PassiveBuzzerQueueWriter& passiveBuzzerQueueWriter,
    SevenSegmentsDisplaysQueueWriter& sevenSegmentsDisplaysQueueWriter,
    SpiOutputQueueWriter& spiOutputQueueWriter)
:
    _i2cOutputQueueWriter(i2cOutputQueueWriter),
    _i2sOutputQueueWriter(i2sOutputQueueWriter),
    _ledStripsQueueWriter(ledStripsQueueWriter),
    _passiveBuzzerQueueWriter(passiveBuzzerQueueWriter),
    _sevenSegmentsDisplaysQueueWriter(sevenSegmentsDisplaysQueueWriter),
    _spiOutputQueueWriter(spiOutputQueueWriter)
{
    // No functionality required.
}

I2cOutputQueueWriter& QueueWriters::GetI2cOutputQueueWriter() 
{
    return _i2cOutputQueueWriter; 
}

I2sOutputQueueWriter& QueueWriters::GetI2sOutputQueueWriter()
{
    return _i2sOutputQueueWriter;
}

LedStripsQueueWriter& QueueWriters::GetLedStripsQueueWriter()
{
    return _ledStripsQueueWriter;
}

PassiveBuzzerQueueWriter& QueueWriters::GetPassiveBuzzerQueueWriter()
{
    return _passiveBuzzerQueueWriter;
}


SevenSegmentsDisplaysQueueWriter& QueueWriters::GetSevenSegmentsDisplaysQueueWriter()
{
    return _sevenSegmentsDisplaysQueueWriter;
}

SpiOutputQueueWriter& QueueWriters::GetSpiOutputQueueWriter()
{
    return _spiOutputQueueWriter;
}
