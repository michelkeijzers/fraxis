#pragma once

#include "../../M00_System/Queues/DiagnosticsQueueReader.hpp"
#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzerQueueReader.hpp"
#include "../../M40_DomainModels/I2c/I2cInputQueueWriter.hpp"
#include "../../M40_DomainModels/I2c/I2cOutputQueueReader.hpp"
#include "../../M40_DomainModels/Spi/SpiInputQueueWriter.hpp"
#include <memory>

class DomainModelsQueueProcessorsContext
{
public:
    DomainModelsQueueProcessorsContext() = default;

    DomainModelsQueueProcessorsContext(
        const DomainModelsQueueProcessorsContext&) = delete;
    
    DomainModelsQueueProcessorsContext& operator=(
        const DomainModelsQueueProcessorsContext&) = delete;
    
    DomainModelsQueueProcessorsContext(
        DomainModelsQueueProcessorsContext&&) = default;

    DomainModelsQueueProcessorsContext& operator=(
        DomainModelsQueueProcessorsContext&&) = default;

    ~DomainModelsQueueProcessorsContext() = default;

    void Set(
        std::unique_ptr<DiagnosticsQueueReader> diagnosticsQueueReader,
        std::unique_ptr<PassiveBuzzerQueueReader> passiveBuzzerQueueReader,
        std::unique_ptr<I2cInputQueueWriter> i2cInputQueueWriter,
        std::unique_ptr<I2cOutputQueueReader> i2cOutputQueueReader,
        std::unique_ptr<SpiInputQueueWriter> spiInputQueueWriter);

    DiagnosticsQueueReader& GetDiagnosticsQueueReader();

    PassiveBuzzerQueueReader& GetPassiveBuzzerQueueReader();

    I2cInputQueueWriter& GetI2cInputQueueWriter();

    I2cOutputQueueReader& GetI2cOutputQueueReader();

    SpiInputQueueWriter& GetSpiInputQueueWriter();

private:
    std::unique_ptr< DiagnosticsQueueReader> _diagnosticsQueueReader = nullptr;

    std::unique_ptr<PassiveBuzzerQueueReader> _passiveBuzzerQueueReader = nullptr;

    std::unique_ptr<I2cOutputQueueReader> _i2cOutputQueueReader = nullptr;

    std::unique_ptr<I2cInputQueueWriter> _i2cInputQueueWriter = nullptr;

    std::unique_ptr<SpiInputQueueWriter> _spiInputQueueWriter = nullptr;
};
