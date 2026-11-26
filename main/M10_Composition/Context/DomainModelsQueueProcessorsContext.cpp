#include "DomainModelsQueueProcessorsContext.hpp"

void DomainModelsQueueProcessorsContext::Set(
    std::unique_ptr< DiagnosticsQueueReader> diagnosticsQueueReader,
    std::unique_ptr<PassiveBuzzerQueueReader> passiveBuzzerQueueReader,
    std::unique_ptr<I2cInputQueueWriter> i2cInputQueueWriter,
    std::unique_ptr<I2cOutputQueueReader> i2cOutputQueueReader,
    std::unique_ptr<I2sInputQueueWriter> i2sInputQueueWriter,
    std::unique_ptr<I2sOutputQueueReader> i2sOutputQueueReader,
    std::unique_ptr<LedStripsQueueReader> ledStripsQueueReader,
    std::unique_ptr<SpiInputQueueWriter> spiInputQueueWriter,
    std::unique_ptr<SpiOutputQueueReader> spiOutputQueueReader)
{
    _diagnosticsQueueReader = std::move(diagnosticsQueueReader);
    _passiveBuzzerQueueReader = std::move(passiveBuzzerQueueReader);
    _i2cInputQueueWriter = std::move(i2cInputQueueWriter);
    _i2cOutputQueueReader = std::move(i2cOutputQueueReader);
    _i2sInputQueueWriter = std::move(i2sInputQueueWriter);
    _i2sOutputQueueReader = std::move(i2sOutputQueueReader);
    _ledStripsQueueReader = std::move(ledStripsQueueReader);
    _spiInputQueueWriter = std::move(spiInputQueueWriter);
    _spiOutputQueueReader = std::move(spiOutputQueueReader);
}

DiagnosticsQueueReader& DomainModelsQueueProcessorsContext::GetDiagnosticsQueueReader()
{
    return *_diagnosticsQueueReader;
}

PassiveBuzzerQueueReader& DomainModelsQueueProcessorsContext::GetPassiveBuzzerQueueReader()
{
    return *_passiveBuzzerQueueReader;
}

I2cInputQueueWriter& DomainModelsQueueProcessorsContext::GetI2cInputQueueWriter()
{
    return *_i2cInputQueueWriter;
}

I2cOutputQueueReader& DomainModelsQueueProcessorsContext::GetI2cOutputQueueReader()
{
    return *_i2cOutputQueueReader;
}

I2sInputQueueWriter& DomainModelsQueueProcessorsContext::GetI2sInputQueueWriter()
{
    return *_i2sInputQueueWriter;
}

I2sOutputQueueReader& DomainModelsQueueProcessorsContext::GetI2sOutputQueueReader()
{
    return *_i2sOutputQueueReader;
}

LedStripsQueueReader& DomainModelsQueueProcessorsContext::GetLedStripsQueueReader()
{
    return *_ledStripsQueueReader;
}

SpiInputQueueWriter& DomainModelsQueueProcessorsContext::GetSpiInputQueueWriter()
{
    return *_spiInputQueueWriter;
}

SpiOutputQueueReader& DomainModelsQueueProcessorsContext::GetSpiOutputQueueReader()
{
    return *_spiOutputQueueReader;
}
