#include "Orchestrator.hpp"
#include "I2cTask.hpp"
#include "LedStripsTask.hpp"
#include "DeviceSettings.hpp"
#include "DeviceSettingsValidator.hpp"
#include "../L1_Composition/Builder/Builder.hpp"
#include "../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../L1_Composition/Context/DeviceDriversContext.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L2_Applications/ApplicationsTask.hpp"
#include "../L4_DomainModels/I2c/Displays/Displays.hpp"
#include "../L4_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../L6_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../L6_DeviceDrivers/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../L6_DeviceDrivers/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../L6_DeviceDrivers/Tm1637/Tm1637DeviceDriver.hpp"
#include "../L6_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include <list>
#include <cstdint>

class Gpio;
class I2c;

Orchestrator::Orchestrator(Builder& builder)
: _builder(builder), _context(nullptr)
{
}

Orchestrator::~Orchestrator()
{
}

void Orchestrator::Run()
{
    _builder.Build();
    _context = &_builder.GetContext();

#ifdef ASSERTS_ENABLED
    ValidateDeviceSettings();
#endif

    CreateLinks();
    InitializeDeviceModels();
    InitializeDevicesDrivers();
    InitializeTasks();
    StartTasks();
}

#ifdef ASSERTS_ENABLED
void Orchestrator::ValidateDeviceSettings()
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
}

void Orchestrator::LinkDomainModelsToDeviceModels()
{
    Context& contextRef = *_context;
    contextRef.GetDomainModels().GetDisplays().GetLcd2004().SetDeviceModel(
        contextRef.GetDeviceModels().GetLcd2004DeviceModel());
    contextRef.GetDomainModels().GetDisplays().GetTm1637CentralPanel().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelCentralPanel());
    contextRef.GetDomainModels().GetDisplays().GetTm1637Player1().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelPlayer1());
    contextRef.GetDomainModels().GetDisplays().GetTm1637Player2().SetDeviceModel(
        contextRef.GetDeviceModels().GetTm1637DeviceModelPlayer2());
    contextRef.GetDomainModels().GetIoPins().SetDeviceModel(
        contextRef.GetDeviceModels().GetMcp23017DeviceModel());
    contextRef.GetDomainModels().GetLedStrips().SetDeviceModel(
        contextRef.GetDeviceModels().GetWs28xxDeviceModel());
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
}

void Orchestrator::LinkDeviceDriversToI2cDeviceDrivers()
{
    Context& contextRef = *_context;
    auto& deviceDrivers = contextRef.GetDeviceDrivers();

    deviceDrivers.GetLcd2004DeviceDriver().SetRtosTask(contextRef.GetTasks().GetI2cTask().GetRtosTask());
    deviceDrivers.GetLcd2004DeviceDriver().SetI2cDeviceDriver(deviceDrivers.GetI2cDeviceDriver());
    deviceDrivers.GetMcp23017DeviceDriver().SetI2cDeviceDriver(deviceDrivers.GetI2cDeviceDriver());
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
}

void Orchestrator::InitializeTasks()
{
    Context& contextRef = *_context;

    auto& applicationsTask = contextRef.GetTasks().GetApplicationsTask();
    applicationsTask.Initialize();

    auto& i2cTask = contextRef.GetTasks().GetI2cTask();
    i2cTask.Initialize();

    auto& ledStripsTask = contextRef.GetTasks().GetLedStripsTask();
    ledStripsTask.Initialize();
}

void Orchestrator::StartTasks()
{
    Context& contextRef = *_context;

    auto& applicationsTask = contextRef.GetTasks().GetApplicationsTask();
    applicationsTask.GetRtosTask().Start();

    auto& i2cTask = contextRef.GetTasks().GetI2cTask();
    i2cTask.GetRtosTask().Start();

    auto& ledStripsTask = contextRef.GetTasks().GetLedStripsTask();
    ledStripsTask.GetRtosTask().Start();
}
