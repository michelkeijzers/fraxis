#pragma once

#include "../../M00_System/Queues/DiagnosticsQueueReader.hpp"
#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzerQueueReader.hpp"
#include "../../M40_DomainModels/I2c/I2cInputQueueWriter.hpp"
#include "../../M40_DomainModels/I2c/I2cOutputQueueReader.hpp"
#include "../../M40_DomainModels/I2s/I2sInputQueueWriter.hpp"
#include "../../M40_DomainModels/I2s/I2sOutputQueueReader.hpp"
#include "../../M40_DomainModels/LedStrips/LedStripsQueueReader.hpp"
#include "../../M40_DomainModels/Spi/SpiInputQueueWriter.hpp"
#include "../../M40_DomainModels/Spi/SpiOutputQueueReader.hpp"
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
        std::unique_ptr<I2sInputQueueWriter> i2sInputQueueWriter,
        std::unique_ptr<I2sOutputQueueReader> i2sOutputQueueReader,
        std::unique_ptr<LedStripsQueueReader> ledStripsQueueReader,
        std::unique_ptr<SpiInputQueueWriter> spiInputQueueWriter,
        std::unique_ptr<SpiOutputQueueReader> spiOutputQueueReader);

    DiagnosticsQueueReader& GetDiagnosticsQueueReader();

    PassiveBuzzerQueueReader& GetPassiveBuzzerQueueReader();

    I2cInputQueueWriter& GetI2cInputQueueWriter();

    I2cOutputQueueReader& GetI2cOutputQueueReader();

    I2sInputQueueWriter& GetI2sInputQueueWriter();

    I2sOutputQueueReader& GetI2sOutputQueueReader();

    LedStripsQueueReader& GetLedStripsQueueReader();

    SpiInputQueueWriter& GetSpiInputQueueWriter();

    SpiOutputQueueReader& GetSpiOutputQueueReader();

private:
    std::unique_ptr< DiagnosticsQueueReader> _diagnosticsQueueReader = nullptr;

    std::unique_ptr<PassiveBuzzerQueueReader> _passiveBuzzerQueueReader = nullptr;

    std::unique_ptr<I2cOutputQueueReader> _i2cOutputQueueReader = nullptr;

    std::unique_ptr<I2cInputQueueWriter> _i2cInputQueueWriter = nullptr;

    std::unique_ptr<I2sOutputQueueReader> _i2sOutputQueueReader = nullptr;

    std::unique_ptr<I2sInputQueueWriter> _i2sInputQueueWriter = nullptr;

    std::unique_ptr<LedStripsQueueReader> _ledStripsQueueReader = nullptr;

    std::unique_ptr<SpiInputQueueWriter> _spiInputQueueWriter = nullptr;

    std::unique_ptr<SpiOutputQueueReader> _spiOutputQueueReader = nullptr;
};
