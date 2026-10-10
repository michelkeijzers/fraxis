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
#include "../M40_DomainModels/Audio/Microphone/Inmp1441.hpp"
#include "../M40_DomainModels/Audio/Dac/Max53987a.hpp"
#include "../M40_DomainModels/Audio/Buzzer/Buzzer.hpp"
#include "../M50_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../M50_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../M50_DeviceModels/Audio/AudioDeviceModel.hpp"
#include "../M50_DeviceModels/Audio/Microphone/MicrophoneDeviceModel.hpp"
#include "../M50_DeviceModels/Audio/Dac/DacDeviceModel.hpp"
#include "../M50_DeviceModels/Audio/Buzzer/BuzzerDeviceModel.hpp"
#include "../M60_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../M60_DeviceDrivers/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../M60_DeviceDrivers/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../M60_DeviceDrivers/Tm1637/Tm1637DeviceDriver.hpp"
#include "../M60_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include "../M60_DeviceDrivers/MicroSdCard/MicroSdCardDeviceDriver.hpp"
#include "../M60_DeviceDrivers/Audio/AudioDeviceDriver.hpp"
#include "../M60_DeviceDrivers/Audio/Microphone/Inmp1441DeviceDriver.hpp"
#include "../M60_DeviceDrivers/Audio/Dac/Max53987aDeviceDriver.hpp"
#include "../M60_DeviceDrivers/Audio/Buzzer/BuzzerDeviceDriver.hpp"
#include "../M80_Services/Nvs/Nvs.hpp"
#include "../M80_Services/Spi/Spi.hpp"
#include "../M80_Services/I2s/I2s.hpp"
#include "../M80_Services/Pwm/Pwm.hpp"
#include "../M90_Utilities/Log/Log.hpp"
#include <list>
#include <cstdint>

class Gpio;
class I2c;
class Nvs;
class I2s;
class Pwm;

Orchestrator::Orchestrator(
    Builder& builder)
:   _builder(builder), 
    _context(nullptr)
{
}

void Orchestrator::Initialize()
{
    _builder.Build();
    _context = &_builder.GetContext();

#ifdef ASSERTS_ENABLED
    ValidateDeviceSettings();
#endif

    InitializeServices();
    CreateLinks();
    InitializeDeviceModels();
    InitializeDevicesDrivers();
    InitializeTasks();
}

#ifdef ASSERTS_ENABLED
void Orchestrator::ValidateDeviceSettings() const
{
    DeviceSettingsValidator::Validate();
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
    contextRef.GetDomainModels().GetMicrophone().SetDeviceModel(
        contextRef.GetDeviceModels().GetMicrophoneDeviceModel());
    contextRef.GetDomainModels().GetDac().SetDeviceModel(
        contextRef.GetDeviceModels().GetDacDeviceModel());
    contextRef.GetDomainModels().GetBuzzer().SetDeviceModel(
        contextRef.GetDeviceModels().GetBuzzerDeviceModel());
}

void Orchestrator::LinkDeviceModelsToDeviceDrivers()
{
    Context& contextRef = *_context;

    auto& lcd2004DeviceDriver = contextRef.GetDeviceDrivers().GetLcd2004DeviceDriver();
    lcd2004DeviceDriver.SetDeviceModel(contextRef.GetDeviceModels().GetLcd2004DeviceModel());

    auto& mcp23017DeviceDriver = contextRef.GetDeviceDrivers().GetMcp23017DeviceDriver();
    mcp23017DeviceDriver.SetDeviceModel(contextRef.GetDeviceModels().GetMcp23017DeviceModel());

    auto& tm1637DeviceDriverCentralPanel = contextRef.GetDeviceDrivers().GetTm1637DeviceDriverCentralPanel();
    tm1637DeviceDriverCentralPanel.SetDeviceModel(contextRef.GetDeviceModels().GetTm1637DeviceModelCentralPanel());

    auto& tm1637DeviceDriverPlayer1 = contextRef.GetDeviceDrivers().GetTm1637DeviceDriverPlayer1();
    tm1637DeviceDriverPlayer1.SetDeviceModel(contextRef.GetDeviceModels().GetTm1637DeviceModelPlayer1());

    auto& tm1637DeviceDriverPlayer2 = contextRef.GetDeviceDrivers().GetTm1637DeviceDriverPlayer2();
    tm1637DeviceDriverPlayer2.SetDeviceModel(contextRef.GetDeviceModels().GetTm1637DeviceModelPlayer2());

    auto& ws28xxDeviceDriver = contextRef.GetDeviceDrivers().GetWs28xxDeviceDriver();
    ws28xxDeviceDriver.SetDeviceModel(contextRef.GetDeviceModels().GetWs28xxDeviceModel());

    auto& MicroSdCardDeviceDriver = contextRef.GetDeviceDrivers().GetMicroSdCardDeviceDriver();
    MicroSdCardDeviceDriver.SetDeviceModel(contextRef.GetDeviceModels().GetMicroSdCardDeviceModel());

    auto& audioDeviceDriver = contextRef.GetDeviceDrivers().GetAudioDeviceDriver();
    audioDeviceDriver.SetDeviceModel(contextRef.GetDeviceModels().GetAudioDeviceModel());

    auto& microphoneDeviceDriver = contextRef.GetDeviceDrivers().GetMicrophoneDeviceDriver();
    microphoneDeviceDriver.SetDeviceModel(contextRef.GetDeviceModels().GetMicrophoneDeviceModel());

    auto& dacDeviceDriver = contextRef.GetDeviceDrivers().GetDacDeviceDriver();
    dacDeviceDriver.SetDeviceModel(contextRef.GetDeviceModels().GetDacDeviceModel());

    auto& buzzerDeviceDriver = contextRef.GetDeviceDrivers().GetBuzzerDeviceDriver();
    buzzerDeviceDriver.SetDeviceModel(contextRef.GetDeviceModels().GetBuzzerDeviceModel());
}

void Orchestrator::LinkDeviceDriversToServices()
{
    Context& contextRef = *_context;

    I2c& i2c = contextRef.GetServices().GetI2c();
    contextRef.GetDeviceDrivers().GetI2cDeviceDriver().SetI2c(i2c);

    Gpio& gpio = contextRef.GetServices().GetGpio();
    contextRef.GetDeviceDrivers().GetMcp23017DeviceDriver().SetGpio(gpio);
    contextRef.GetDeviceDrivers().GetTm1637DeviceDriverCentralPanel().SetGpio(gpio);
    contextRef.GetDeviceDrivers().GetTm1637DeviceDriverPlayer1().SetGpio(gpio);
    contextRef.GetDeviceDrivers().GetTm1637DeviceDriverPlayer2().SetGpio(gpio);

    Spi& spi = contextRef.GetServices().GetSpi();
    contextRef.GetDeviceDrivers().GetSpiDeviceDriver().SetSpi(spi);

    I2s& i2s = contextRef.GetServices().GetI2s();
    contextRef.GetDeviceDrivers().GetAudioDeviceDriver().SetI2s(i2s);
    contextRef.GetDeviceDrivers().GetMicrophoneDeviceDriver().SetI2s(i2s);
    contextRef.GetDeviceDrivers().GetDacDeviceDriver().SetI2s(i2s);

    Pwm& pwm = contextRef.GetServices().GetPwm();
    contextRef.GetDeviceDrivers().GetBuzzerDeviceDriver().SetPwm(pwm);
}

void Orchestrator::LinkDeviceDriversToI2cDeviceDrivers()
{
    Context& contextRef = *_context;
    auto& deviceDrivers = contextRef.GetDeviceDrivers();

    deviceDrivers.GetLcd2004DeviceDriver().SetRtosTask(contextRef.GetTasks().GetI2cTask().GetRtosTask());
    deviceDrivers.GetLcd2004DeviceDriver().SetI2cDeviceDriver(deviceDrivers.GetI2cDeviceDriver());
    deviceDrivers.GetMcp23017DeviceDriver().SetI2cDeviceDriver(deviceDrivers.GetI2cDeviceDriver());
}

void Orchestrator::LinkDeviceDriversToSpiDeviceDrivers()
{
    Context& contextRef = *_context;
    auto& deviceDrivers = contextRef.GetDeviceDrivers();

    deviceDrivers.GetMicroSdCardDeviceDriver().SetSpiDeviceDriver(deviceDrivers.GetSpiDeviceDriver());
}

void Orchestrator::LinkDeviceDriversToAudioDeviceDrivers()
{
    Context& contextRef = *_context;
    auto& deviceDrivers = contextRef.GetDeviceDrivers();

    deviceDrivers.GetAudioDeviceDriver().SetRtosTask(contextRef.GetTasks().GetAudioTask().GetRtosTask());
    deviceDrivers.GetMicrophoneDeviceDriver().SetRtosTask(contextRef.GetTasks().GetAudioTask().GetRtosTask());
    deviceDrivers.GetDacDeviceDriver().SetRtosTask(contextRef.GetTasks().GetAudioTask().GetRtosTask());
    deviceDrivers.GetBuzzerDeviceDriver().SetRtosTask(contextRef.GetTasks().GetAudioTask().GetRtosTask());
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
    std::list<uint8_t> inputBits = 
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
    tm1637DeviceModelCentralPanel.SetNrOfDigits(4);
    tm1637DeviceModelCentralPanel.Initialize();

    auto& tm1637DeviceModelPlayer1 = deviceModels.GetTm1637DeviceModelPlayer1();
    tm1637DeviceModelPlayer1.SetNrOfDigits(6);
    tm1637DeviceModelPlayer1.Initialize();

    auto& tm1637DeviceModelPlayer2 = deviceModels.GetTm1637DeviceModelPlayer2();
    tm1637DeviceModelPlayer2.SetNrOfDigits(6);
    tm1637DeviceModelPlayer2.Initialize();

    auto& ws28xxDeviceModel = deviceModels.GetWs28xxDeviceModel();
    ws28xxDeviceModel.SetMaxCurrentConsumption(DeviceSettings::MAX_LED_STRIPS_CURRENT_CONSUMPTION_IN_MA);
    ws28xxDeviceModel.SetNrOfLeds(LedStrips::NUMBER_OF_LEDS);
    ws28xxDeviceModel.Initialize();

    auto& microSdCardDeviceModel = deviceModels.GetMicroSdCardDeviceModel();
    //TODOSD
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

    auto& microphoneDeviceModel = deviceModels.GetMicrophoneDeviceModel();
    microphoneDeviceModel.SetI2sPort(DeviceSettings::I2S_PORT);
    microphoneDeviceModel.Initialize();

    auto& dacDeviceModel = deviceModels.GetDacDeviceModel();
    dacDeviceModel.SetI2sPort(DeviceSettings::I2S_PORT);
    dacDeviceModel.Initialize();

    auto& buzzerDeviceModel = deviceModels.GetBuzzerDeviceModel();
    buzzerDeviceModel.SetPwmPin(DeviceSettings::PIN_BUZZER);
    buzzerDeviceModel.Initialize();
}

void Orchestrator::InitializeDevicesDrivers()
{
    Context& contextRef = *_context;

    auto& i2cDeviceDriver = contextRef.GetDeviceDrivers().GetI2cDeviceDriver();
    i2cDeviceDriver.SetConfiguration(DeviceSettings::I2C_PORT, DeviceSettings::PIN_I2C_SDA, DeviceSettings::PIN_I2C_SCL, 
        DeviceSettings::I2C_FREQUENCY);
    i2cDeviceDriver.Initialize();

    auto& lcd2004DeviceDriver = contextRef.GetDeviceDrivers().GetLcd2004DeviceDriver();
    lcd2004DeviceDriver.Initialize();

    auto& mcp23017DeviceDriver = contextRef.GetDeviceDrivers().GetMcp23017DeviceDriver();
    mcp23017DeviceDriver.SetInterruptConfiguration(true, DeviceSettings::PIN_MCP23017_INTERRUPT);
    mcp23017DeviceDriver.Initialize();

    auto& tm1637DeviceDriverCentralPanel = contextRef.GetDeviceDrivers().GetTm1637DeviceDriverCentralPanel();
    tm1637DeviceDriverCentralPanel.SetPinsConfiguration(
        DeviceSettings::PIN_TM1637_CLOCK, DeviceSettings::PIN_TM1637_CENTRAL_PANEL_DATA);
    tm1637DeviceDriverCentralPanel.Initialize();

    auto& tm1637DeviceDriverPlayer1 = contextRef.GetDeviceDrivers().GetTm1637DeviceDriverPlayer1();
    tm1637DeviceDriverPlayer1.SetPinsConfiguration(
        DeviceSettings::PIN_TM1637_CLOCK, DeviceSettings::PIN_TM1637_PLAYER_1_DATA);
    tm1637DeviceDriverPlayer1.Initialize();

    auto& tm1637DeviceDriverPlayer2 = contextRef.GetDeviceDrivers().GetTm1637DeviceDriverPlayer2();
    tm1637DeviceDriverPlayer2.SetPinsConfiguration(
        DeviceSettings::PIN_TM1637_CLOCK, DeviceSettings::PIN_TM1637_PLAYER_2_DATA);
    tm1637DeviceDriverPlayer2.Initialize();

    auto& ws28xxDeviceDriver = contextRef.GetDeviceDrivers().GetWs28xxDeviceDriver();
    ws28xxDeviceDriver.SetRmt(contextRef.GetServices().GetRmt());
    ws28xxDeviceDriver.SetDataPin(DeviceSettings::PIN_WS2812_DATA);
    ws28xxDeviceDriver.Initialize();

    auto& spiDeviceDriver = contextRef.GetDeviceDrivers().GetSpiDeviceDriver();
    //TODOSPI
    spiDeviceDriver.Initialize();

    auto& audioDeviceDriver = contextRef.GetDeviceDrivers().GetAudioDeviceDriver();
    audioDeviceDriver.SetConfiguration(DeviceSettings::I2S_PORT, DeviceSettings::PIN_I2S_BCLK, DeviceSettings::PIN_I2S_WS, DeviceSettings::PIN_I2S_DIN, DeviceSettings::PIN_I2S_DOUT, DeviceSettings::I2S_SAMPLE_RATE, DeviceSettings::I2S_BITS_PER_SAMPLE, DeviceSettings::I2S_CHANNELS);
    audioDeviceDriver.Initialize();

    auto& microphoneDeviceDriver = contextRef.GetDeviceDrivers().GetMicrophoneDeviceDriver();
    microphoneDeviceDriver.SetConfiguration(DeviceSettings::I2S_PORT, DeviceSettings::PIN_I2S_BCLK, DeviceSettings::PIN_I2S_WS, DeviceSettings::PIN_I2S_DIN, DeviceSettings::PIN_I2S_DOUT, DeviceSettings::I2S_SAMPLE_RATE, DeviceSettings::I2S_BITS_PER_SAMPLE, DeviceSettings::I2S_CHANNELS);
    microphoneDeviceDriver.Initialize();

    auto& dacDeviceDriver = contextRef.GetDeviceDrivers().GetDacDeviceDriver();
    dacDeviceDriver.SetConfiguration(DeviceSettings::I2S_PORT, DeviceSettings::PIN_I2S_BCLK, DeviceSettings::PIN_I2S_WS, DeviceSettings::PIN_I2S_DIN, DeviceSettings::PIN_I2S_DOUT, DeviceSettings::I2S_SAMPLE_RATE, DeviceSettings::I2S_BITS_PER_SAMPLE, DeviceSettings::I2S_CHANNELS);
    dacDeviceDriver.Initialize();

    auto& buzzerDeviceDriver = contextRef.GetDeviceDrivers().GetBuzzerDeviceDriver();
    buzzerDeviceDriver.SetConfiguration(DeviceSettings::PIN_BUZZER);
    buzzerDeviceDriver.Initialize();
}

void Orchestrator::InitializeTasks()
{
    Context& contextRef = *_context;

    auto& applicationsTask = contextRef.GetTasks().GetApplicationsTask();
    applicationsTask.Initialize();

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
}

void Orchestrator::StartTasks()
{
    Log::Entry(Types::ETaskId::System, "Orchestrator::StartTasks()");

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

    Log::Exit(Types::ETaskId::System, "Orchestrator::StartTasks()");
}
