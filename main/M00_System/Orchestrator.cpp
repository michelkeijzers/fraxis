#include "Orchestrator.hpp"
#include "DeviceSettings.hpp"
#include "DeviceSettingsValidator.hpp"
#include "Tasks/DiagnosticsTask.hpp"
#include "Tasks/I2cTask.hpp"
#include "Tasks/I2sTask.hpp"
#include "Tasks/LedStripsTask.hpp"
#include "Tasks/PassiveBuzzerTask.hpp"
#include "Tasks/SevenSegmentsDisplaysTask.hpp"
#include "Tasks/SpiTask.hpp"
#include "../M10_Composition/Builder/Builder.hpp"
#include "../M10_Composition/Context/DeviceModelsContext.hpp"
#include "../M10_Composition/Context/DeviceDriversContext.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M20_Applications/ApplicationsTask.hpp"
#include "../M40_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../M40_DomainModels/I2c/Lcd2004/Lcd2004.hpp"
#include "../M40_DomainModels/SevenSegmentsDisplays/Tm1637.hpp"
#include "../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../M40_DomainModels/Spi/MicroSdCard/MicroSdCard.hpp"
#include "../M40_DomainModels/I2s/I2sMicrophone/I2sMicrophone.hpp"
#include "../M40_DomainModels/I2s/I2sDac/I2sDac.hpp"
#include "../M40_DomainModels/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../M50_DeviceModels/I2c/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../M50_DeviceModels/I2c/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../M50_DeviceModels/SevenSegmentsDisplays/Tm1637/Tm1637DeviceModel.hpp"
#include "../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../M50_DeviceModels/Spi/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../M50_DeviceModels/I2s/I2sDeviceModel.hpp"
#include "../M50_DeviceModels/I2s/Inmp1441/Inmp1441DeviceModel.hpp"
#include "../M50_DeviceModels/I2s/Max53987a/Max53987aDeviceModel.hpp"
#include "../M50_DeviceModels/PassiveBuzzer/PassiveBuzzerDeviceModel.hpp"
#include "../M60_DeviceDrivers/DeviceDriver.hpp"
#include "../M60_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../M60_DeviceDrivers/I2c/Lcd2004/ILcd2004DeviceDriver.hpp"
#include "../M60_DeviceDrivers/I2c/Mcp23017/IMcp23017DeviceDriver.hpp"
#include "../M60_DeviceDrivers/SevenSegmentsDisplays/Tm1637DeviceDriver.hpp"
#include "../M60_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include "../M60_DeviceDrivers/Spi/MicroSdCard/MicroSdCardDeviceDriver.hpp"
#include "../M60_DeviceDrivers/I2s/I2sDeviceDriver.hpp"
#include "../M60_DeviceDrivers/I2s/Inmp1441/Inmp1441DeviceDriver.hpp"
#include "../M60_DeviceDrivers/I2s/Max53987a/Max53987aDeviceDriver.hpp"
#include "../M60_DeviceDrivers/PassiveBuzzer/PassiveBuzzerDeviceDriver.hpp"
#include "../M80_Services/Nvs/INvs.hpp"
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

    namespace PassiveBuzzer
    {
        class IPassiveBuzzer;
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
    // TODO: All following methods should be removed (top to bottom).
    LinkDomainModelsToDeviceModels();
    LinkDeviceModelsToDeviceDrivers();
    LinkDeviceDriversToServices();
    LinkDeviceDriversToI2cTask();
    LinkDeviceDriversToI2sTask();

    // Link all instances from bottom to top. 
    // All other instances have been coupled in the constructors in the build phase.
    LinkDeviceDriversToDeviceModels();
    LinkServicesToQueues();
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
   
    deviceDriversContext.GetTm1637DeviceDriverCentralPanel().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelCentralPanel());

    deviceDriversContext.GetTm1637DeviceDriverPlayer1().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelPlayer1());

    deviceDriversContext.GetTm1637DeviceDriverPlayer2().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelPlayer2());

    deviceDriversContext.GetWs28xxDeviceDriver().SetDeviceModel(
        contextRef.GetDeviceModels().GetWs28xxDeviceModel());

    deviceDriversContext.GetWs28xxDeviceDriver().SetDeviceModel(
        contextRef.GetDeviceModels().GetWs28xxDeviceModel());

    deviceDriversContext.GetI2sDeviceDriver().SetDeviceModel(
        contextRef.GetDeviceModels().GetI2sDeviceModel());

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

    M80::I2s::II2sService& i2s = contextRef.GetServices().GetI2s();
    deviceDriversContext.GetI2sDeviceDriver().SetI2s(i2s);
    deviceDriversContext.GetInmp1441DeviceDriver().SetI2s(i2s);
    deviceDriversContext.GetMax53987aDeviceDriver().SetI2s(i2s);

    M80::Pwm::IPwm& pwm = contextRef.GetServices().GetPwm();
    deviceDriversContext.GetPassiveBuzzerDeviceDriver().SetPwm(pwm);
}

void Orchestrator::LinkDeviceDriversToI2cTask()
{
    Context& contextRef = *_context;
    DeviceDriversContext& deviceDriversContext = contextRef.GetDeviceDrivers();

    deviceDriversContext.GetLcd2004DeviceDriver().SetRtosTask(
        contextRef.GetTasks().GetI2cTask().GetRtosTask());
}

void Orchestrator::LinkDeviceDriversToI2sTask()
{
    Context& contextRef = *_context;
    DeviceDriversContext& deviceDriversContext = contextRef.GetDeviceDrivers();

    deviceDriversContext.GetI2sDeviceDriver().SetRtosTask(
        contextRef.GetTasks().GetI2sTask().GetRtosTask());
    deviceDriversContext.GetInmp1441DeviceDriver().SetRtosTask(
        contextRef.GetTasks().GetI2sTask().GetRtosTask());
    deviceDriversContext.GetMax53987aDeviceDriver().SetRtosTask(
        contextRef.GetTasks().GetI2sTask().GetRtosTask());
    deviceDriversContext.GetPassiveBuzzerDeviceDriver().SetRtosTask(
        contextRef.GetTasks().GetI2sTask().GetRtosTask());
}

void Orchestrator::LinkDeviceDriversToDeviceModels()
{
    Context& contextRef = *_context;

    auto& lcd2004DeviceDriver = static_cast<M60::I2c::Lcd2004DeviceDriver&>(
        contextRef.GetDeviceDrivers().GetLcd2004DeviceDriver());
    lcd2004DeviceDriver.SetDeviceModel(_context->GetDeviceModels().GetLcd2004DeviceModel());

    auto& mcp23017DeviceDriver = static_cast<M60::I2c::Mcp23017DeviceDriver&>(
        contextRef.GetDeviceDrivers().GetMcp23017DeviceDriver());
    mcp23017DeviceDriver.SetDeviceModel(_context->GetDeviceModels().GetMcp23017DeviceModel());
}

void Orchestrator::LinkServicesToQueues()
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

    auto& i2sDeviceModel = deviceModels.GetI2sDeviceModel();
    i2sDeviceModel.SetPort(DeviceSettings::I2S_PORT);
    i2sDeviceModel.SetBclkPin(DeviceSettings::PIN_I2S_BCLK);
    i2sDeviceModel.SetWsPin(DeviceSettings::PIN_I2S_WS);
    i2sDeviceModel.SetDinPin(DeviceSettings::PIN_I2S_DIN);
    i2sDeviceModel.SetDoutPin(DeviceSettings::PIN_I2S_DOUT);
    i2sDeviceModel.SetSampleRate(DeviceSettings::I2S_SAMPLE_RATE);
    i2sDeviceModel.SetBitsPerSample(DeviceSettings::I2S_BITS_PER_SAMPLE);
    i2sDeviceModel.SetChannels(DeviceSettings::I2S_CHANNELS);
    i2sDeviceModel.Initialize();

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

    deviceDriversContext.GetI2cDeviceDriver().Initialize();

    auto& lcd2004DeviceDriver = static_cast<M60::I2c::Lcd2004DeviceDriver&>(
        contextRef.GetDeviceDrivers().GetLcd2004DeviceDriver());
    lcd2004DeviceDriver.Initialize();

    auto& mcp23017DeviceDriver = static_cast<M60::I2c::Mcp23017DeviceDriver&>(
        contextRef.GetDeviceDrivers().GetMcp23017DeviceDriver());
    mcp23017DeviceDriver.Initialize();

    deviceDriversContext.GetTm1637DeviceDriverCentralPanel().Initialize();

    deviceDriversContext.GetTm1637DeviceDriverPlayer1().Initialize();

    deviceDriversContext.GetTm1637DeviceDriverPlayer2().Initialize();

    deviceDriversContext.GetWs28xxDeviceDriver().Initialize();

    deviceDriversContext.GetSpiDeviceDriver().Initialize();

    deviceDriversContext.GetI2sDeviceDriver().SetConfiguration(
        DeviceSettings::I2S_PORT, 
        DeviceSettings::PIN_I2S_BCLK, 
        DeviceSettings::PIN_I2S_WS, 
        DeviceSettings::PIN_I2S_DIN, 
        DeviceSettings::PIN_I2S_DOUT, 
        DeviceSettings::I2S_SAMPLE_RATE, 
        DeviceSettings::I2S_BITS_PER_SAMPLE, 
        DeviceSettings::I2S_CHANNELS);
    deviceDriversContext.GetI2sDeviceDriver().Initialize();

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

    auto& sevenSegmentsDisplaysTask = contextRef.GetTasks().GetSevenSegmentsDisplaysTask();
    sevenSegmentsDisplaysTask.Initialize();

    auto& spiTask = contextRef.GetTasks().GetSpiTask();
    spiTask.Initialize();

    auto& ledStripsTask = contextRef.GetTasks().GetLedStripsTask();
    ledStripsTask.Initialize();

    auto& diagnosticsTask = contextRef.GetTasks().GetDiagnosticsTask();
    diagnosticsTask.Initialize();

    auto& i2sTask = contextRef.GetTasks().GetI2sTask();
    i2sTask.Initialize();

    auto& passiveBuzzerTask = contextRef.GetTasks().GetPassiveBuzzerTask();
    passiveBuzzerTask.Initialize();

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

    auto& sevenSegmentsDisplaysTask = contextRef.GetTasks().GetSevenSegmentsDisplaysTask();
    sevenSegmentsDisplaysTask.GetRtosTask().Start();

    auto& spiTask = contextRef.GetTasks().GetSpiTask();
    spiTask.GetRtosTask().Start();

    auto& ledStripsTask = contextRef.GetTasks().GetLedStripsTask();
    ledStripsTask.GetRtosTask().Start();

    auto& diagnosticsTask = contextRef.GetTasks().GetDiagnosticsTask();
    diagnosticsTask.GetRtosTask().Start();

    auto& i2sTask = contextRef.GetTasks().GetI2sTask();
    i2sTask.GetRtosTask().Start();

    auto& passiveBuzzerTask = contextRef.GetTasks().GetPassiveBuzzerTask();
    passiveBuzzerTask.GetRtosTask().Start();

    _context->GetUtilities().GetLog().Exit(Types::ETaskId::System, "Orchestrator::StartTasks()");
}
