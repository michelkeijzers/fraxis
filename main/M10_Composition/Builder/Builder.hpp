#pragma once

#include "../Context/Context.hpp"
#include <memory>

class I2cOutputQueue;
class I2cOutputQueueReader;
class I2cInputQueueWriter;
class SpiInputQueue;
class SpiInputQueueWriter;
class IoPins;
class Lcd2004;
class MicroSdCard;
class Mcp23017DeviceModel;

namespace M60::I2c
{
    class I2cTaskDeviceDriversDelegate;
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
        I2cInputQueue& i2cInputQueue,
        I2cOutputQueue& i2cOutputQueue,
        SpiInputQueue& spiInputQueue,
        Lcd2004& lcd2004,
        IoPins& ioPins,
        PassiveBuzzerQueue& passiveBuzzerOutputQueue,
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
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::Time::ITimeUtilities& timeUtilities);

    virtual void BuildQueuesContext(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);
    
    virtual void BuildTasksContext(
        I2cOutputQueueReader& i2cOutputQueueReader,
        SpiInputQueueWriter& spiInputQueueWriter,
        PassiveBuzzerQueueReader& passiveBuzzerQueueReader,
        M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate&
            passiveBuzzerTaskDeviceDriversDelegate,
        M60::Ws28xx::IWs28xxDeviceDriver& ws28xxDeviceDriver,
        M60::I2c::I2cTaskDeviceDriversDelegate& i2cTaskDeviceDriversDelegate,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
        M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
        M80::Random::IRandom& random,
        M90::Assert::IAssert& assert,
        M90::Container::IContainerUtilities& containerUtilities,
        M90::Log::ILog& log,
        M90::Math::IMathUtilities& mathUtilities,
        M90::String::IStringUtilities& stringUtilities,
        M90::Time::ITimeUtilities& timeUtilities);

private:
    std::unique_ptr<Context> _context;
};