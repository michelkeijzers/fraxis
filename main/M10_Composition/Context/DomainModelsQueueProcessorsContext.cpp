#include "DomainModelsQueueProcessorsContext.hpp"

void DomainModelsQueueProcessorsContext::Set(
    std::unique_ptr< DiagnosticsQueueReader> diagnosticsQueueReader,
    std::unique_ptr<PassiveBuzzerQueueReader> passiveBuzzerQueueReader,
    std::unique_ptr<I2cInputQueueWriter> i2cInputQueueWriter,
    std::unique_ptr<I2cOutputQueueReader> i2cOutputQueueReader,
    std::unique_ptr<SpiInputQueueWriter> spiInputQueueWriter)
{
    _diagnosticsQueueReader = std::move(diagnosticsQueueReader);
    _passiveBuzzerQueueReader = std::move(passiveBuzzerQueueReader);
    _i2cInputQueueWriter = std::move(i2cInputQueueWriter);
    _i2cOutputQueueReader = std::move(i2cOutputQueueReader);
    _spiInputQueueWriter = std::move(spiInputQueueWriter);
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

SpiInputQueueWriter& DomainModelsQueueProcessorsContext::GetSpiInputQueueWriter()
{
    return *_spiInputQueueWriter;
}
