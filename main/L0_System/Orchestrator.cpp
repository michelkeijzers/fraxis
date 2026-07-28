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
#include "../L5_DeviceModels/Ws28xx/Ws28xxModel.hpp"
#include "../L5_DeviceModels/Mcp23017/Mcp23017Model.hpp"
#include "../L5_DeviceModels/Lcd2004/Lcd2004Model.hpp"
#include "../L5_DeviceModels/Tm1637/Tm1637Model.hpp"
#include "../L6_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include "../L6_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../L6_DeviceDrivers/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../L6_DeviceDrivers/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../L6_DeviceDrivers/Tm1637/Tm1637DeviceDriver.hpp"
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
    _context->GetDomainModels().GetDisplays().SetDeviceModelsContext(_context->GetDeviceModels());

    auto& deviceDrivers = _context->GetDeviceDrivers();
    deviceDrivers.GetLcd2004DeviceDriver().SetI2cDeviceDriver(deviceDrivers.GetI2cDeviceDriver());
    deviceDrivers.GetMcp23017DeviceDriver().SetI2cDeviceDriver(deviceDrivers.GetI2cDeviceDriver());
    LinkDeviceModelsToDeviceDrivers();
}

void Orchestrator::LinkDeviceModelsToDeviceDrivers()
{
    auto& ws28xxDeviceDriver = _context->GetDeviceDrivers().GetWs28xxDeviceDriver();
    auto& mcp23017DeviceDriver = _context->GetDeviceDrivers().GetMcp23017DeviceDriver();
    auto& lcd2004DeviceDriver = _context->GetDeviceDrivers().GetLcd2004DeviceDriver();
    auto& tm1637DeviceDriverCentralPanel = _context->GetDeviceDrivers().GetTm1637DeviceDriverCentralPanel();
    auto& tm1637DeviceDriverPlayer1 = _context->GetDeviceDrivers().GetTm1637DeviceDriverPlayer1();
    auto& tm1637DeviceDriverPlayer2 = _context->GetDeviceDrivers().GetTm1637DeviceDriverPlayer2();

    ws28xxDeviceDriver.SetDeviceModel(_context->GetDeviceModels().GetLedStripModel());
    mcp23017DeviceDriver.SetDeviceModel(_context->GetDeviceModels().GetMcp23017Model());
    lcd2004DeviceDriver.SetDeviceModel(_context->GetDeviceModels().GetLcd2004Model());
    tm1637DeviceDriverCentralPanel.SetDeviceModel(_context->GetDeviceModels().GetTm1637ModelCentralPanel());
    tm1637DeviceDriverPlayer1.SetDeviceModel(_context->GetDeviceModels().GetTm1637ModelPlayer1());
    tm1637DeviceDriverPlayer2.SetDeviceModel(_context->GetDeviceModels().GetTm1637ModelPlayer2());
}

void Orchestrator::InitializeDeviceModels()
{
    auto& deviceModels = _context->GetDeviceModels();
    auto& ws28xxModel = deviceModels.GetLedStripModel();
    auto& mcp23017Model = deviceModels.GetMcp23017Model();
    auto& lcd2004Model = deviceModels.GetLcd2004Model();
    auto& tm1637ModelCentralPanel = deviceModels.GetTm1637ModelCentralPanel();
    auto& tm1637ModelPlayer1 = deviceModels.GetTm1637ModelPlayer1();
    auto& tm1637ModelPlayer2 = deviceModels.GetTm1637ModelPlayer2();

    ws28xxModel.Initialize();

    mcp23017Model.SetI2cAddress(DeviceSettings::I2C_ADDRESS_MCP23017);
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
    mcp23017Model.SetInputBits(inputBits);
    mcp23017Model.Initialize();

    lcd2004Model.SetI2cAddress(DeviceSettings::I2C_ADDRESS_LCD2004);
    lcd2004Model.Initialize();

    tm1637ModelCentralPanel.Initialize();
    tm1637ModelPlayer1.Initialize();
    tm1637ModelPlayer2.Initialize();
}

void Orchestrator::InitializeDevicesDrivers()
{
    auto& ws28xxDeviceDriver = _context->GetDeviceDrivers().GetWs28xxDeviceDriver();
    auto& i2cDeviceDriver = _context->GetDeviceDrivers().GetI2cDeviceDriver();
    auto& mcp23017DeviceDriver = _context->GetDeviceDrivers().GetMcp23017DeviceDriver();
    auto& lcd2004DeviceDriver = _context->GetDeviceDrivers().GetLcd2004DeviceDriver();
    auto& tm1637DeviceDriverCentralPanel = _context->GetDeviceDrivers().GetTm1637DeviceDriverCentralPanel();
    auto& tm1637DeviceDriverPlayer1 = _context->GetDeviceDrivers().GetTm1637DeviceDriverPlayer1();
    auto& tm1637DeviceDriverPlayer2 = _context->GetDeviceDrivers().GetTm1637DeviceDriverPlayer2();

    ws28xxDeviceDriver.Initialize();
    i2cDeviceDriver.SetConfiguration(DeviceSettings::I2C_PORT, DeviceSettings::PIN_I2C_SDA, DeviceSettings::PIN_I2C_SCL, 
        DeviceSettings::I2C_FREQUENCY);
    i2cDeviceDriver.Initialize();
    mcp23017DeviceDriver.Initialize();
    lcd2004DeviceDriver.Initialize();
    tm1637DeviceDriverCentralPanel.Initialize();
    tm1637DeviceDriverPlayer1.Initialize();
    tm1637DeviceDriverPlayer2.Initialize();
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
