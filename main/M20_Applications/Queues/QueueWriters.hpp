#pragma once

// TODO What about DiagnosticsQueueWriter? (does not exist)

class I2cOutputQueueWriter;
class I2sOutputQueueWriter;
class LedStripsQueueWriter;
class PassiveBuzzerQueueWriter;
class SevenSegmentsDisplaysQueueWriter;
class SpiOutputQueueWriter;

class QueueWriters
{
public:
    QueueWriters(
        I2cOutputQueueWriter& i2cOutputQueueWriter,
        I2sOutputQueueWriter& i2sOutputQueueWriter,
        LedStripsQueueWriter& ledStripsQueueWriter,
        PassiveBuzzerQueueWriter& passiveBuzzerQueueWriter,
        SevenSegmentsDisplaysQueueWriter& sevenSegmentsDisplaysQueueWriter,
        SpiOutputQueueWriter& spiOutputQueueWriter);

    QueueWriters(
        const QueueWriters&) = delete;

    QueueWriters& operator=(
        const QueueWriters&) = delete;

    QueueWriters(
        QueueWriters&&) = delete;

    QueueWriters& operator=(
        QueueWriters&&) = delete;

    ~QueueWriters() = default;

    I2cOutputQueueWriter& GetI2cOutputQueueWriter();

    I2sOutputQueueWriter& GetI2sOutputQueueWriter();

    LedStripsQueueWriter& GetLedStripsQueueWriter();

    PassiveBuzzerQueueWriter& GetPassiveBuzzerQueueWriter();

    SevenSegmentsDisplaysQueueWriter& GetSevenSegmentsDisplaysQueueWriter();

    SpiOutputQueueWriter& GetSpiOutputQueueWriter();


private:
    I2cOutputQueueWriter& _i2cOutputQueueWriter;

    I2sOutputQueueWriter& _i2sOutputQueueWriter;
    
    LedStripsQueueWriter& _ledStripsQueueWriter;

    PassiveBuzzerQueueWriter& _passiveBuzzerQueueWriter;
    
    SevenSegmentsDisplaysQueueWriter& _sevenSegmentsDisplaysQueueWriter;
   
    SpiOutputQueueWriter& _spiOutputQueueWriter;
};
