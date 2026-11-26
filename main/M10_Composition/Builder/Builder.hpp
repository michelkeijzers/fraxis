#pragma once

#include "../Context/Context.hpp"
#include <memory>

class WatchDog;
class DiagnosticsManager;
class DiagnosticsQueue;
class I2cInputQueue;
class I2cOutputQueue;
class I2cOutputQueueReader;
class I2cInputQueueWriter;
class I2sInputQueue;
class I2sOutputQueue;
class I2sOutputQueueReader;
class I2sInputQueueWriter;
class SpiInputQueue;
class SpiOutputQueue;
class SpiInputQueueWriter;
class SpiOutputQeuueReader;
class IoPins;
class Lcd2004;
class MicroSdCard;
class Mcp23017DeviceModel;

namespace M60::I2c
{
    class I2cTaskDeviceDriversDelegate;
}

namespace M60::I2s
{
    class I2sTaskDeviceDriversDelegate;
}

namespace M60::PassiveBuzzer
{
    class PassiveBuzzerTaskDeviceDriversDelegate;
}

namespace M60::Ws28xx
{
    class Ws28xxDeviceDriver;
}

namespace M80::Random
{
    class IRandom;
}

namespace M80::Uart
{
    class IUart;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

namespace M90::Container
{
    class IContainerUtilities;
}

namespace M90::Log
{
    class Ilog;
}

namespace M90::Math
{
    class IMathUtilities;
}

namespace M90::String
{
    class IStringUtilities;
}

namespace M90::Time
{
    class ITimeUtilities;
}

class PassiveBuzzerQueue;

class Builder
{
public:
    explicit Builder();

    Builder(
        const Builder&) = delete;
    
    Builder& operator=(
        const Builder&) = delete;
    
    Builder(
        Builder&&) = delete;
    
    Builder& operator=(
        Builder&&) = delete;

    virtual ~Builder() = default;

    Context& GetContext();
    
    void Build();

protected:
    virtual void BuildUtilitiesContext();

    virtual void BuildServicesContext() = 0;

    virtual void BuildDeviceDriversContext(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities);
        
    virtual void BuildDeviceModelsContext(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::Container::IContainerUtilities& containerUtilities,
        M90::String::IStringUtilities& stringUtilities);

    virtual void BuildDomainModelsContext(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::Algorithm::IAlgorithm& algorithm);
    
    virtual void BuildDomainModelsQueueProcessorsContext(
        DiagnosticsQueue& diagnosticsQueue,
        WatchDog& watchDog,
        DiagnosticsManager& diagnosticsManager,
        I2cInputQueue& i2cInputQueue,
        I2cOutputQueue& i2cOutputQueue,
        I2sInputQueue& i2sInputQueue,
        I2sOutputQueue& i2sOutputQueue,
        LedStripsQueue& ledStripsQueue,
        SpiInputQueue& spiInputQueue,
        SpiOutputQueue& spiOutputQueue,
        Lcd2004& lcd2004,
        LedStrips& ledStrips,
        IoPins& ioPins,
        I2sDac& i2sDac,
        I2sMicrophone& i2sMicrophone,
        I2sMixer& i2sMixer,
        PassiveBuzzerQueue& passiveBuzzerQueue,
        PassiveBuzzer& passiveBuzzer,
        MicroSdCard& microSdCard,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);

    virtual void BuildTaskDeviceDriversDelegates(
        I2cInputQueueWriter& i2cInputQueueWriter,
        IoPins& ioPins,
        Mcp23017DeviceModel& mcp23017DeviceModel,
        M60::I2c::ILcd2004DeviceDriver& lcd2004DeviceDriver,
        M60::I2c::IMcp23017DeviceDriver& mcp23017DeviceDriver,
        M60::Ws28xx::IWs28xxDeviceDriver& ws28xxDeviceDriver,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::Time::ITimeUtilities& timeUtilities);

    virtual void BuildQueuesContext(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);
    
    virtual void BuildTasksContext(
        WatchDog& watchDog,
        DiagnosticsQueueReader& diagnosticsQueueReader,
        I2cOutputQueueReader& i2cOutputQueueReader,
        I2sOutputQueueReader& i2sOutputQueueReader,
        LedStripsQueueReader& ledStripsQueueReader,
        SpiOutputQueueReader& spiOutputQueueReader,
        PassiveBuzzerQueueReader& passiveBuzzerQueueReader,
        M60::I2c::I2cTaskDeviceDriversDelegate& i2cTaskDeviceDriversDelegate,
        M60::I2s::I2sTaskDeviceDriversDelegate& i2sTaskDeviceDriversDelegate,
        M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate&
            passiveBuzzerTaskDeviceDriversDelegate,
        M60::Spi::SpiTaskDeviceDriversDelegate& spiTaskDeviceDriversDelegate,
        M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate& ws28xxTaskDeviceDriversDelegate,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
        M80::Random::IRandom& random,
        M80::Uart::IUart& uart,
        M90::Assert::IAssert& assert,
        M90::Container::IContainerUtilities& containerUtilities,
        M90::Log::ILog& log,
        M90::Math::IMathUtilities& mathUtilities,
        M90::String::IStringUtilities& stringUtilities,
        M90::Time::ITimeUtilities& timeUtilities);

    virtual void BuildSystemContext(
        M80::Uart::IUart& uart,
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities,
        M90::Time::ITimeUtilities& timeUtilities);

private:
    std::unique_ptr<Context> _context;
};