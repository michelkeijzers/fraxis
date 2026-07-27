#pragma once

class I2cOutputQueueWriter;
class LedStripsQueueWriter;

class QueueWriters
{
public:
    QueueWriters(I2cOutputQueueWriter& i2cOutputQueueWriter, LedStripsQueueWriter& ledStripsQueueWriter);
    ~QueueWriters();

    I2cOutputQueueWriter& GetI2cOutputQueueWriter();
    LedStripsQueueWriter& GetLedStripsQueueWriter();

private:
    I2cOutputQueueWriter& _i2cOutputQueueWriter;
    LedStripsQueueWriter& _ledStripsQueueWriter;
};
