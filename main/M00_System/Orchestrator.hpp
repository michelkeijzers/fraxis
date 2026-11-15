#pragma once 

#include "../M90_Utilities/Assert/Assert.hpp"

namespace M90::Assert
{
    class IAssert;
}

class Builder;
class Context;

namespace M60::Lcd2004
{
    class Lcd2004DeviceDriver;
}

namespace M60::Mcp23017
{
    class Mcp23017DeviceDriver;
}

namespace M60::I2c
{
class Tm1637DeviceDriver;
}

namespace M60::Ws28xx
{
    class Ws28xxDeviceDriver;
}

namespace M60::Spi
{
    class MicroSdCardDeviceDriver;
}

namespace M60::Audio
{
    class AudioDeviceDriver;
    class Inmp1441DeviceDriver;
    class Max53987aDeviceDriver;
    class BuzzerDeviceDriver;
}

class Orchestrator
{
public:
    explicit Orchestrator(
        Builder& builder);

    Orchestrator(
        const Orchestrator&) = delete;
    
    Orchestrator& operator=(
        const Orchestrator&) = delete;
    
    Orchestrator(
        Orchestrator&&) = delete;
    
    Orchestrator& operator=(
        Orchestrator&&) = delete;
    
    ~Orchestrator() = default;

    void Initialize(
        M60::Lcd2004::Lcd2004DeviceDriver& lcd2004DeviceDriver,
        M60::Mcp23017::Mcp23017DeviceDriver& mcp23017DeviceDriver,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
        M60::Ws28xx::Ws28xxDeviceDriver& ws28xxDeviceDriver,
        M60::Spi::MicroSdCardDeviceDriver& microSdCardDeviceDriver,
        M60::Audio::AudioDeviceDriver& audioDeviceDriver,
        M60::Audio::Inmp1441DeviceDriver& inmp1441DeviceDriver,
        M60::Audio::Max53987aDeviceDriver& max53987aDeviceDriver,
        M60::Audio::BuzzerDeviceDriver& buzzerDeviceDriver);
    
    void StartTasks();

private:
    Builder& _builder;
    
    Context* _context = nullptr;

#ifdef ASSERTS_ENABLED
    void ValidateDeviceSettings(
        M90::Assert::IAssert& assert) const;
#endif // ASSERTS_ENABLED

    void CreateLinks(
        M60::Lcd2004::Lcd2004DeviceDriver& lcd2004DeviceDriver,
        M60::Mcp23017::Mcp23017DeviceDriver& mcp23017DeviceDriver,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
        M60::Ws28xx::Ws28xxDeviceDriver& ws28xxDeviceDriver,
        M60::Spi::MicroSdCardDeviceDriver& microSdCardDeviceDriver,
        M60::Audio::AudioDeviceDriver& audioDeviceDriver,
        M60::Audio::Inmp1441DeviceDriver& inmp1441DeviceDriver,
        M60::Audio::Max53987aDeviceDriver& max53987aDeviceDriver,
        M60::Audio::BuzzerDeviceDriver& buzzerDeviceDriver);
    
    void LinkDomainModelsToDeviceModels();
    
    void LinkDeviceModelsToDeviceDrivers(
        M60::Lcd2004::Lcd2004DeviceDriver &lcd2004DeviceDriver,
        M60::Mcp23017::Mcp23017DeviceDriver &mcp23017DeviceDriver,
        M60::I2c::Tm1637DeviceDriver &tm1637DeviceDriverCentralPanel,
        M60::I2c::Tm1637DeviceDriver &tm1637DeviceDriverPlayer1,
        M60::I2c::Tm1637DeviceDriver &tm1637DeviceDriverPlayer2,
        M60::Ws28xx::Ws28xxDeviceDriver &ws28xxDeviceDriver,
        M60::Spi::MicroSdCardDeviceDriver &microSdCardDeviceDriver,
        M60::Audio::AudioDeviceDriver &audioDeviceDriver,
        M60::Audio::Inmp1441DeviceDriver &inmp1441DeviceDriver,
        M60::Audio::Max53987aDeviceDriver &max53987aDeviceDriver,
        M60::Audio::BuzzerDeviceDriver &buzzerDeviceDriver);
    
    void InitializeServices();
    
    void LinkDeviceDriversToServices();
    
    void LinkDeviceDriversToI2cDeviceDrivers();
    
    void LinkDeviceDriversToSpiDeviceDrivers();
    
    void LinkDeviceDriversToAudioDeviceDrivers();

    void InitializeDeviceModels();
    
    void InitializeDevicesDrivers();
    
    void InitializeTasks();
};
