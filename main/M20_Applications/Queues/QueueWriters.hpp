#pragma once

class I2cOutputQueueWriter;
class SpiOutputQueueWriter;
class LedStripsQueueWriter;

class QueueWriters
{
public:
    QueueWriters(
        I2cOutputQueueWriter& i2cOutputQueueWriter,
        SpiOutputQueueWriter& spiOutputQueueWriter, 
        LedStripsQueueWriter& ledStripsQueueWriter);
    ~QueueWriters();

    I2cOutputQueueWriter& GetI2cOutputQueueWriter();
    SpiOutputQueueWriter& GetSpiOutputQueueWriter();
    LedStripsQueueWriter& GetLedStripsQueueWriter();

private:
    I2cOutputQueueWriter& _i2cOutputQueueWriter;
    SpiOutputQueueWriter& _spiOutputQueueWriter;
    LedStripsQueueWriter& _ledStripsQueueWriter;
};
