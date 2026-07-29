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

Orchestrator::Orchestrator(Builder& builder)
: _builder(builder)
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
    //_context->GetDomainModels().GetDisplays().SetDeviceModelsContext(_context->GetDeviceModels());
    _context->GetDomainModels().GetDisplays().GetLcd2004().SetDeviceModel(
        _context->GetDeviceModels().GetLcd2004DeviceModel());
    _context->GetDomainModels().GetDisplays().GetTm1637CentralPanel().SetDeviceModel(
        _context->GetDeviceModels().GetTm1637DeviceModelCentralPanel());
    _context->GetDomainModels().GetDisplays().GetTm1637Player1().SetDeviceModel(
        _context->GetDeviceModels().GetTm1637DeviceModelPlayer1());
    _context->GetDomainModels().GetDisplays().GetTm1637Player2().SetDeviceModel(
        _context->GetDeviceModels().GetTm1637DeviceModelPlayer2());
    _context->GetDomainModels().GetIoPins().SetDeviceModel(
        _context->GetDeviceModels().GetMcp23017DeviceModel());
    _context->GetDomainModels().GetLedStrips().SetDeviceModel(
        _context->GetDeviceModels().GetWs28xxDeviceModel());

    auto& deviceDrivers = _context->GetDeviceDrivers();
    deviceDrivers.GetLcd2004DeviceDriver().SetI2cDeviceDriver(deviceDrivers.GetI2cDeviceDriver());
    deviceDrivers.GetMcp23017DeviceDriver().SetI2cDeviceDriver(deviceDrivers.GetI2cDeviceDriver());
    LinkDeviceModelsToDeviceDrivers();
}

void Orchestrator::LinkDeviceModelsToDeviceDrivers()
{
    auto& lcd2004DeviceDriver = _context->GetDeviceDrivers().GetLcd2004DeviceDriver();
    auto& mcp23017DeviceDriver = _context->GetDeviceDrivers().GetMcp23017DeviceDriver();
    auto& tm1637DeviceDriverCentralPanel = _context->GetDeviceDrivers().GetTm1637DeviceDriverCentralPanel();
    auto& tm1637DeviceDriverPlayer1 = _context->GetDeviceDrivers().GetTm1637DeviceDriverPlayer1();
    auto& tm1637DeviceDriverPlayer2 = _context->GetDeviceDrivers().GetTm1637DeviceDriverPlayer2();
    auto& ws28xxDeviceDriver = _context->GetDeviceDrivers().GetWs28xxDeviceDriver();

    lcd2004DeviceDriver.SetDeviceModel(_context->GetDeviceModels().GetLcd2004DeviceModel());
    mcp23017DeviceDriver.SetDeviceModel(_context->GetDeviceModels().GetMcp23017DeviceModel());
    tm1637DeviceDriverCentralPanel.SetDeviceModel(_context->GetDeviceModels().GetTm1637DeviceModelCentralPanel());
    tm1637DeviceDriverPlayer1.SetDeviceModel(_context->GetDeviceModels().GetTm1637DeviceModelPlayer1());
    tm1637DeviceDriverPlayer2.SetDeviceModel(_context->GetDeviceModels().GetTm1637DeviceModelPlayer2());
    ws28xxDeviceDriver.SetDeviceModel(_context->GetDeviceModels().GetWs28xxDeviceModel());
}

void Orchestrator::InitializeDeviceModels()
{
    auto& deviceModels = _context->GetDeviceModels();
    auto& lcd2004DeviceModel = deviceModels.GetLcd2004DeviceModel();
    auto& mcp23017DeviceModel = deviceModels.GetMcp23017DeviceModel();
    auto& tm1637DeviceModelCentralPanel = deviceModels.GetTm1637DeviceModelCentralPanel();
    auto& tm1637DeviceModelPlayer1 = deviceModels.GetTm1637DeviceModelPlayer1();
    auto& tm1637DeviceModelPlayer2 = deviceModels.GetTm1637DeviceModelPlayer2();
    auto& ws28xxDeviceModel = deviceModels.GetWs28xxDeviceModel();

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
    mcp23017DeviceModel.SetInputBits(inputBits);
    mcp23017DeviceModel.SetI2cAddress(DeviceSettings::I2C_ADDRESS_MCP23017);
    mcp23017DeviceModel.Initialize();
    tm1637DeviceModelCentralPanel.SetNrOfDigits(4);
    tm1637DeviceModelCentralPanel.Initialize();
    tm1637DeviceModelPlayer1.SetNrOfDigits(6);
    tm1637DeviceModelPlayer1.Initialize();
    tm1637DeviceModelPlayer2.SetNrOfDigits(6);
    tm1637DeviceModelPlayer2.Initialize();
    ws28xxDeviceModel.Initialize();
}

void Orchestrator::InitializeDevicesDrivers()
{
    auto& i2cDeviceDriver = _context->GetDeviceDrivers().GetI2cDeviceDriver();
    auto& lcd2004DeviceDriver = _context->GetDeviceDrivers().GetLcd2004DeviceDriver();
    auto& mcp23017DeviceDriver = _context->GetDeviceDrivers().GetMcp23017DeviceDriver();
    auto& tm1637DeviceDriverCentralPanel = _context->GetDeviceDrivers().GetTm1637DeviceDriverCentralPanel();
    auto& tm1637DeviceDriverPlayer1 = _context->GetDeviceDrivers().GetTm1637DeviceDriverPlayer1();
    auto& tm1637DeviceDriverPlayer2 = _context->GetDeviceDrivers().GetTm1637DeviceDriverPlayer2();
    auto& ws28xxDeviceDriver = _context->GetDeviceDrivers().GetWs28xxDeviceDriver();

    i2cDeviceDriver.SetConfiguration(DeviceSettings::I2C_PORT, DeviceSettings::PIN_I2C_SDA, DeviceSettings::PIN_I2C_SCL, 
        DeviceSettings::I2C_FREQUENCY);
    i2cDeviceDriver.Initialize();
    lcd2004DeviceDriver.Initialize();
    mcp23017DeviceDriver.SetInterruptConfiguration(true, DeviceSettings::PIN_MCP23017_INTERRUPT);
    mcp23017DeviceDriver.Initialize();
    tm1637DeviceDriverCentralPanel.SetPinsConfiguration(
        DeviceSettings::PIN_TM1637_CLOCK, DeviceSettings::PIN_TM1637_CENTRAL_PANEL_DATA);
    tm1637DeviceDriverCentralPanel.Initialize();
    tm1637DeviceDriverPlayer1.SetPinsConfiguration(
        DeviceSettings::PIN_TM1637_CLOCK, DeviceSettings::PIN_TM1637_PLAYER_1_DATA);
    tm1637DeviceDriverPlayer1.Initialize();
    tm1637DeviceDriverPlayer2.SetPinsConfiguration(
        DeviceSettings::PIN_TM1637_CLOCK, DeviceSettings::PIN_TM1637_PLAYER_2_DATA);
    tm1637DeviceDriverPlayer2.Initialize();
    ws28xxDeviceDriver.Initialize();
}

void Orchestrator::InitializeTasks()
{
    auto& applicationsTask = _context->GetTasks().GetApplicationsTask();
    auto& i2cTask = _context->GetTasks().GetI2cTask();
    auto& ledStripsTask = _context->GetTasks().GetLedStripsTask();

    applicationsTask.Initialize();
    i2cTask.Initialize();
    ledStripsTask.Initialize();
}

void Orchestrator::StartTasks()
{
    auto& applicationsTask = _context->GetTasks().GetApplicationsTask();
    auto& i2cTask = _context->GetTasks().GetI2cTask();
    auto& ledStripsTask = _context->GetTasks().GetLedStripsTask();

    applicationsTask.GetRtosTask().Start();
    i2cTask.GetRtosTask().Start();
    ledStripsTask.GetRtosTask().Start();
}
