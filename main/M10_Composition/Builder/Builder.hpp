#pragma once

#include "../Context/Context.hpp"
#include <memory>

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

namespace M90::Container
{
    class IContainerUtilities;
}

namespace M90::Log
{
    class Ilog;
}

namespace M90::String
{
    class IStringUtilities;
}

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
        M90::Container::IContainerUtilities& containerUtilities,
        M90::String::IStringUtilities& stringUtilities);

    virtual void BuildDomainModelsContext(
        M90::Assert::IAssert& assert,
        M90::Algorithm::IAlgorithm& algorithm);

    virtual void BuildQueuesContext(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities);
    
    virtual void BuildTasksContext(
        M60::Ws28xx::Ws28xxDeviceDriver& ws28xxDeviceDriver,
        M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver,
        M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
        M80::Random::IRandom& random,
        M90::Assert::IAssert& assert,
        M90::Container::IContainerUtilities& containerUtilities,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);

    std::unique_ptr<Context> _context;
};