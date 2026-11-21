#include "Orchestrator.hpp"
#include "DiagnosticsTask.hpp"
#include "DeviceSettings.hpp"
#include "DeviceSettingsValidator.hpp"
#include "I2cTask.hpp"
#include "SpiTask.hpp"
#include "LedStripsTask.hpp"
#include "AudioTask.hpp"
#include "../M10_Composition/Builder/Builder.hpp"
#include "../M10_Composition/Context/DeviceModelsContext.hpp"
#include "../M10_Composition/Context/DeviceDriversContext.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M20_Applications/ApplicationsTask.hpp"
#include "../M40_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../M40_DomainModels/I2c/Displays/Tm1637/Tm1637.hpp"
#include "../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../M40_DomainModels/Spi/MicroSdCard/MicroSdCard.hpp"
#include "../M40_DomainModels/Audio/I2sMicrophone/I2sMicrophone.hpp"
#include "../M40_DomainModels/Audio/I2sDac/I2sDac.hpp"
#include "../M40_DomainModels/Audio/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../M50_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../M50_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../M50_DeviceModels/Audio/AudioDeviceModel.hpp"
#include "../M50_DeviceModels/Audio/Inmp1441/Inmp1441DeviceModel.hpp"
#include "../M50_DeviceModels/Audio/Max53987a/Max53987aDeviceModel.hpp"
#include "../M50_DeviceModels/Audio/PassiveBuzzer/PassiveBuzzerDeviceModel.hpp"
#include "../M60_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../M60_DeviceDrivers/I2c/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../M60_DeviceDrivers/I2c/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../M60_DeviceDrivers/I2c/Tm1637/Tm1637DeviceDriver.hpp"
#include "../M60_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include "../M60_DeviceDrivers/Spi/MicroSdCard/MicroSdCardDeviceDriver.hpp"
#include "../M60_DeviceDrivers/Audio/AudioDeviceDriver.hpp"
#include "../M60_DeviceDrivers/Audio/Inmp1441/Inmp1441DeviceDriver.hpp"
#include "../M60_DeviceDrivers/Audio/Max53987a/Max53987aDeviceDriver.hpp"
#include "../M60_DeviceDrivers/Audio/PassiveBuzzer/PassiveBuzzerDeviceDriver.hpp"
#include "../M80_Services/Nvs/INvs.hpp"
#include "../M80_Services/Spi/ISpi.hpp"
#include "../M80_Services/I2s/I2s.hpp"
#include "../M80_Services/Pwm/IPwm.hpp"
#include "../M80_Services/Gpio/Gpio.hpp"
#include "../M81_RtosServices/RtosTask/IRtosTask.hpp"
#include "../M90_Utilities/Log/Log.hpp"
#include <list>
#include <cstdint>

namespace M80
{
    namespace I2c
    {
        class II2c;
    }

    namespace I2s
    {
        class II2s;
    }
    
    namespace Nvs
    {
        class INvs;
    }
    
    namespace Pwm
    {
       class IPwm;
    }

    namespace Spi
    {
        class ISpi;
    }

    namespace Uart
    {
        class IUart;
    }
}

Orchestrator::Orchestrator(
    Builder& builder)
:   
    _builder(builder)
{
}

void Orchestrator::Initialize()
{
    _builder.Build();
    _context = &_builder.GetContext();

#ifdef ASSERTS_ENABLED
    ValidateDeviceSettings(_context->GetUtilities().GetAssert());
#endif

    InitializeServices();

    CreateLinks();

    InitializeDeviceModels();

    InitializeDevicesDrivers();

    InitializeTasks();
}

#ifdef ASSERTS_ENABLED
void Orchestrator::ValidateDeviceSettings(
    M90::Assert::IAssert& assert) const
{
    DeviceSettingsValidator validator(assert);
    validator.Validate();
}
#endif // TRACE_ENABLED

void Orchestrator::CreateLinks()
{
    LinkDomainModelsToDeviceModels();
    LinkDeviceModelsToDeviceDrivers();
    LinkDeviceDriversToServices();
    LinkDeviceDriversToI2cDeviceDrivers();
    LinkDeviceDriversToSpiDeviceDrivers();
    LinkDeviceDriversToAudioDeviceDrivers();
    LinkServices();
}

void Orchestrator::LinkDomainModelsToDeviceModels()
{
    Context& contextRef = *_context;
    contextRef.GetDomainModels().GetLcd2004().SetDeviceModel(
        contextRef.GetDeviceModels().GetLcd2004DeviceModel());
    contextRef.GetDomainModels().GetTm1637CentralPanel().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelCentralPanel());
    contextRef.GetDomainModels().GetTm1637Player1().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelPlayer1());
    contextRef.GetDomainModels().GetTm1637Player2().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelPlayer2());
    contextRef.GetDomainModels().GetIoPins().SetDeviceModel(
        contextRef.GetDeviceModels().GetMcp23017DeviceModel());
    contextRef.GetDomainModels().GetLedStrips().SetDeviceModel(
        contextRef.GetDeviceModels().GetWs28xxDeviceModel());
    contextRef.GetDomainModels().GetMicroSdCard().SetDeviceModel(
        contextRef.GetDeviceModels().GetMicroSdCardDeviceModel());
    contextRef.GetDomainModels().GetI2sMicrophone().SetDeviceModel(
        contextRef.GetDeviceModels().GetInmp1441DeviceModel());
    contextRef.GetDomainModels().GetI2sDac().SetDeviceModel(
        contextRef.GetDeviceModels().GetMax53987aDeviceModel());
    contextRef.GetDomainModels().GetPassiveBuzzer().SetDeviceModel(
        contextRef.GetDeviceModels().GetPassiveBuzzerDeviceModel());
}

void Orchestrator::LinkDeviceModelsToDeviceDrivers()
{
    Context& contextRef = *_context;
    DeviceDriversContext& deviceDriversContext = contextRef.GetDeviceDrivers();
   
    deviceDriversContext.GetLcd2004DeviceDriver().SetDeviceModel(
        contextRef.GetDeviceModels().GetLcd2004DeviceModel());

    deviceDriversContext.GetMcp23017DeviceDriver().SetDeviceModel(
        contextRef.GetDeviceModels().GetMcp23017DeviceModel());

    deviceDriversContext.GetTm1637DeviceDriverCentralPanel().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelCentralPanel());

    deviceDriversContext.GetTm1637DeviceDriverPlayer1().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelPlayer1());

    deviceDriversContext.GetTm1637DeviceDriverPlayer2().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelPlayer2());

    deviceDriversContext.GetWs28xxDeviceDriver().SetDeviceModel(
        contextRef.GetDeviceModels().GetWs28xxDeviceModel());

    deviceDriversContext.GetAudioDeviceDriver().SetDeviceModel(
        contextRef.GetDeviceModels().GetAudioDeviceModel());

    deviceDriversContext.GetInmp1441DeviceDriver().SetDeviceModel(
        contextRef.GetDeviceModels().GetInmp1441DeviceModel());

    deviceDriversContext.GetMax53987aDeviceDriver().SetDeviceModel(
        contextRef.GetDeviceModels().GetMax53987aDeviceModel());

    deviceDriversContext.GetPassiveBuzzerDeviceDriver().SetDeviceModel(
        contextRef.GetDeviceModels().GetPassiveBuzzerDeviceModel());
}

void Orchestrator::LinkDeviceDriversToServices()
{
    Context& contextRef = *_context;
    DeviceDriversContext& deviceDriversContext = contextRef.GetDeviceDrivers();

    M80::I2c::II2c& i2c = contextRef.GetServices().GetI2c();
    deviceDriversContext.GetI2cDeviceDriver().SetI2c(i2c);

    M80::Gpio::IGpio& gpio = contextRef.GetServices().GetGpio();
    deviceDriversContext.GetMcp23017DeviceDriver().SetGpio(gpio);
    deviceDriversContext.GetTm1637DeviceDriverCentralPanel().SetGpio(gpio);
    deviceDriversContext.GetTm1637DeviceDriverPlayer1().SetGpio(gpio);
    deviceDriversContext.GetTm1637DeviceDriverPlayer2().SetGpio(gpio);

    M80::Spi::ISpi& spi = contextRef.GetServices().GetSpi();
    deviceDriversContext.GetSpiDeviceDriver().SetSpi(spi);

    M80::I2s::II2s& i2s = contextRef.GetServices().GetI2s();
    deviceDriversContext.GetAudioDeviceDriver().SetI2s(i2s);
    deviceDriversContext.GetInmp1441DeviceDriver().SetI2s(i2s);
    deviceDriversContext.GetMax53987aDeviceDriver().SetI2s(i2s);

    M80::Pwm::IPwm& pwm = contextRef.GetServices().GetPwm();
    deviceDriversContext.GetPassiveBuzzerDeviceDriver().SetPwm(pwm);
}

void Orchestrator::LinkDeviceDriversToI2cDeviceDrivers()
{
    Context& contextRef = *_context;
    DeviceDriversContext& deviceDriversContext = contextRef.GetDeviceDrivers();

    deviceDriversContext.GetLcd2004DeviceDriver().SetRtosTask(
        contextRef.GetTasks().GetI2cTask().GetRtosTask());
    deviceDriversContext.GetLcd2004DeviceDriver().SetI2cDeviceDriver(
        deviceDriversContext.GetI2cDeviceDriver());
    deviceDriversContext.GetMcp23017DeviceDriver().SetI2cDeviceDriver(
        deviceDriversContext.GetI2cDeviceDriver());
}

void Orchestrator::LinkDeviceDriversToSpiDeviceDrivers()
{
    Context& contextRef = *_context;
    DeviceDriversContext& deviceDriversContext = contextRef.GetDeviceDrivers();

    deviceDriversContext.GetMicroSdCardDeviceDriver().SetSpiDeviceDriver(
        deviceDriversContext.GetSpiDeviceDriver());
}

void Orchestrator::LinkDeviceDriversToAudioDeviceDrivers()
{
    Context& contextRef = *_context;
    DeviceDriversContext& deviceDriversContext = contextRef.GetDeviceDrivers();

    deviceDriversContext.GetAudioDeviceDriver().SetRtosTask(
        contextRef.GetTasks().GetAudioTask().GetRtosTask());
    deviceDriversContext.GetInmp1441DeviceDriver().SetRtosTask(
        contextRef.GetTasks().GetAudioTask().GetRtosTask());
    deviceDriversContext.GetMax53987aDeviceDriver().SetRtosTask(
        contextRef.GetTasks().GetAudioTask().GetRtosTask());
    deviceDriversContext.GetPassiveBuzzerDeviceDriver().SetRtosTask(
        contextRef.GetTasks().GetAudioTask().GetRtosTask());
}

void Orchestrator::LinkServices()
{
    Context& contextRef = *_context;

    contextRef.GetUtilities().GetLog().SetDiagnostics(
        contextRef.GetQueues().GetDiagnosticsQueue(),
        contextRef.GetQueues().GetDiagnosticsQueueWriter());
}

void Orchestrator::InitializeServices()
{
    Context& contextRef = *_context;

    auto& nvs = contextRef.GetServices().GetNvs();
    nvs.Initialize();
}

void Orchestrator::InitializeDeviceModels()
{
    Context& contextRef = *_context;
    auto& deviceModels = contextRef.GetDeviceModels();

    auto& lcd2004DeviceModel = deviceModels.GetLcd2004DeviceModel();
    lcd2004DeviceModel.SetI2cAddress(DeviceSettings::I2C_ADDRESS_LCD2004);
    lcd2004DeviceModel.Initialize();
    std::list inputBits = // uint8_t
    {
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_UP,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_DOWN,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_LEFT,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_RIGHT,
        DeviceSettings::MCP23017_BIT_PLAYER_1_JOYSTICK_BUTTON,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_UP,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_DOWN,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_LEFT,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_RIGHT,
        DeviceSettings::MCP23017_BIT_PLAYER_2_JOYSTICK_BUTTON,
        DeviceSettings::MCP23017_BIT_SYSTEM_BUTTON
    };

    auto& mcp23017DeviceModel = deviceModels.GetMcp23017DeviceModel();
    mcp23017DeviceModel.SetInputBits(inputBits);
    mcp23017DeviceModel.SetI2cAddress(DeviceSettings::I2C_ADDRESS_MCP23017);
    mcp23017DeviceModel.Initialize();

    auto& tm1637DeviceModelCentralPanel = deviceModels.GetTm1637DeviceModelCentralPanel();
    tm1637DeviceModelCentralPanel.SetNumberOfDigits(
        DeviceSettings::TM1637_CENTRAL_PANEL_NUMBER_OF_DIGITS);
    tm1637DeviceModelCentralPanel.Initialize();

    auto& tm1637DeviceModelPlayer1 = deviceModels.GetTm1637DeviceModelPlayer1();
    tm1637DeviceModelPlayer1.SetNumberOfDigits(DeviceSettings::TM1637_PLAYERS_NUMBER_OF_DIGITS);
    tm1637DeviceModelPlayer1.Initialize();

    auto& tm1637DeviceModelPlayer2 = deviceModels.GetTm1637DeviceModelPlayer2();
    tm1637DeviceModelPlayer2.SetNumberOfDigits(DeviceSettings::TM1637_PLAYERS_NUMBER_OF_DIGITS);
    tm1637DeviceModelPlayer2.Initialize();

    auto& ws28xxDeviceModel = deviceModels.GetWs28xxDeviceModel();
    ws28xxDeviceModel.SetMaxCurrentConsumption(
        DeviceSettings::MAX_LED_STRIPS_CURRENT_CONSUMPTION_IN_MA);
    ws28xxDeviceModel.SetNumberOfLeds(LedStrips::NUMBER_OF_LEDS);
    ws28xxDeviceModel.Initialize();

    auto& microSdCardDeviceModel = deviceModels.GetMicroSdCardDeviceModel();
    // NOSONAR TODO SD
    microSdCardDeviceModel.Initialize();

    auto& audioDeviceModel = deviceModels.GetAudioDeviceModel();
    audioDeviceModel.SetPort(DeviceSettings::I2S_PORT);
    audioDeviceModel.SetBclkPin(DeviceSettings::PIN_I2S_BCLK);
    audioDeviceModel.SetWsPin(DeviceSettings::PIN_I2S_WS);
    audioDeviceModel.SetDinPin(DeviceSettings::PIN_I2S_DIN);
    audioDeviceModel.SetDoutPin(DeviceSettings::PIN_I2S_DOUT);
    audioDeviceModel.SetSampleRate(DeviceSettings::I2S_SAMPLE_RATE);
    audioDeviceModel.SetBitsPerSample(DeviceSettings::I2S_BITS_PER_SAMPLE);
    audioDeviceModel.SetChannels(DeviceSettings::I2S_CHANNELS);
    audioDeviceModel.Initialize();

    auto& inmp1441DeviceModel = deviceModels.GetInmp1441DeviceModel();
    inmp1441DeviceModel.SetI2sPort(DeviceSettings::I2S_PORT);
    inmp1441DeviceModel.Initialize();

    auto& max53987aDeviceModel = deviceModels.GetMax53987aDeviceModel();
    max53987aDeviceModel.SetI2sPort(DeviceSettings::I2S_PORT);
    max53987aDeviceModel.Initialize();

    auto& passiveBuzzerDeviceModel = deviceModels.GetPassiveBuzzerDeviceModel();
    passiveBuzzerDeviceModel.SetPwmPin(DeviceSettings::PIN_PASSIVE_BUZZER);
    passiveBuzzerDeviceModel.Initialize();
}

void Orchestrator::InitializeDevicesDrivers()
{
    Context& contextRef = *_context;
    DeviceDriversContext& deviceDriversContext = contextRef.GetDeviceDrivers();

    deviceDriversContext.GetI2cDeviceDriver().SetConfiguration(
        DeviceSettings::I2C_PORT, DeviceSettings::PIN_I2C_SDA, DeviceSettings::PIN_I2C_SCL, 
        DeviceSettings::I2C_FREQUENCY);
    deviceDriversContext.GetI2cDeviceDriver().Initialize();

    deviceDriversContext.GetLcd2004DeviceDriver().Initialize();

    deviceDriversContext.GetMcp23017DeviceDriver().SetInterruptConfiguration(
        true, DeviceSettings::PIN_MCP23017_INTERRUPT);
    deviceDriversContext.GetMcp23017DeviceDriver().Initialize();

    deviceDriversContext.GetTm1637DeviceDriverCentralPanel().SetPinsConfiguration(
        DeviceSettings::PIN_TM1637_CLOCK, DeviceSettings::PIN_TM1637_CENTRAL_PANEL_DATA);
    deviceDriversContext.GetTm1637DeviceDriverCentralPanel().Initialize();

    deviceDriversContext.GetTm1637DeviceDriverPlayer1().SetPinsConfiguration(
        DeviceSettings::PIN_TM1637_CLOCK, DeviceSettings::PIN_TM1637_PLAYER_1_DATA);
    deviceDriversContext.GetTm1637DeviceDriverPlayer1().Initialize();

    deviceDriversContext.GetTm1637DeviceDriverPlayer2().SetPinsConfiguration(
        DeviceSettings::PIN_TM1637_CLOCK, DeviceSettings::PIN_TM1637_PLAYER_2_DATA);
    deviceDriversContext.GetTm1637DeviceDriverPlayer2().Initialize();

    deviceDriversContext.GetWs28xxDeviceDriver().SetRmt(contextRef.GetServices().GetRmt());
    deviceDriversContext.GetWs28xxDeviceDriver().SetDataPin(DeviceSettings::PIN_WS2812_DATA);
    deviceDriversContext.GetWs28xxDeviceDriver().Initialize();

    // NOSONAR TODO SPI
    deviceDriversContext.GetSpiDeviceDriver().Initialize();

    deviceDriversContext.GetAudioDeviceDriver().SetConfiguration(
        DeviceSettings::I2S_PORT, 
        DeviceSettings::PIN_I2S_BCLK, 
        DeviceSettings::PIN_I2S_WS, 
        DeviceSettings::PIN_I2S_DIN, 
        DeviceSettings::PIN_I2S_DOUT, 
        DeviceSettings::I2S_SAMPLE_RATE, 
        DeviceSettings::I2S_BITS_PER_SAMPLE, 
        DeviceSettings::I2S_CHANNELS);
    deviceDriversContext.GetAudioDeviceDriver().Initialize();

    deviceDriversContext.GetInmp1441DeviceDriver().SetConfiguration(
        DeviceSettings::I2S_PORT, 
        DeviceSettings::PIN_I2S_BCLK, 
        DeviceSettings::PIN_I2S_WS,
        DeviceSettings::PIN_I2S_DIN, 
        DeviceSettings::PIN_I2S_DOUT, 
        DeviceSettings::I2S_SAMPLE_RATE, 
        DeviceSettings::I2S_BITS_PER_SAMPLE, 
        DeviceSettings::I2S_CHANNELS);
    deviceDriversContext.GetInmp1441DeviceDriver().Initialize();

    deviceDriversContext.GetMax53987aDeviceDriver().SetConfiguration(
        DeviceSettings::I2S_PORT, 
        DeviceSettings::PIN_I2S_BCLK, 
        DeviceSettings::PIN_I2S_WS, 
        DeviceSettings::PIN_I2S_DIN, 
        DeviceSettings::PIN_I2S_DOUT, 
        DeviceSettings::I2S_SAMPLE_RATE, 
        DeviceSettings::I2S_BITS_PER_SAMPLE, 
        DeviceSettings::I2S_CHANNELS);
    deviceDriversContext.GetMax53987aDeviceDriver().Initialize();

    deviceDriversContext.GetPassiveBuzzerDeviceDriver().SetConfiguration(
        DeviceSettings::PIN_PASSIVE_BUZZER);
    deviceDriversContext.GetPassiveBuzzerDeviceDriver().Initialize();
}

void Orchestrator::InitializeTasks()
{
    Context& contextRef = *_context;

    auto& applicationsTask = contextRef.GetTasks().GetApplicationsTask();

    auto& i2cTask = contextRef.GetTasks().GetI2cTask();
    i2cTask.Initialize();

    auto& spiTask = contextRef.GetTasks().GetSpiTask();
    spiTask.Initialize();

    auto& ledStripsTask = contextRef.GetTasks().GetLedStripsTask();
    ledStripsTask.Initialize();

    auto& diagnosticsTask = contextRef.GetTasks().GetDiagnosticsTask();
    diagnosticsTask.Initialize();

    auto& audioTask = contextRef.GetTasks().GetAudioTask();
    audioTask.Initialize();

    applicationsTask.Initialize();
}

void Orchestrator::StartTasks()
{
    _context->GetUtilities().GetLog().Entry(Types::ETaskId::System, "Orchestrator::StartTasks()");

    Context& contextRef = *_context;

    auto& applicationsTask = contextRef.GetTasks().GetApplicationsTask();
    applicationsTask.GetRtosTask().Start();

    auto& i2cTask = contextRef.GetTasks().GetI2cTask();
    i2cTask.GetRtosTask().Start();

    auto& spiTask = contextRef.GetTasks().GetSpiTask();
    spiTask.GetRtosTask().Start();

    auto& ledStripsTask = contextRef.GetTasks().GetLedStripsTask();
    ledStripsTask.GetRtosTask().Start();

    auto& diagnosticsTask = contextRef.GetTasks().GetDiagnosticsTask();
    diagnosticsTask.GetRtosTask().Start();

    auto& audioTask = contextRef.GetTasks().GetAudioTask();
    audioTask.GetRtosTask().Start();

    _context->GetUtilities().GetLog().Exit(Types::ETaskId::System, "Orchestrator::StartTasks()");
}
