#include "Orchestrator.hpp"
#include "I2cTask.hpp"
#include "LedStripsTask.hpp"
#include "../L1_Composition/Builder/Builder.hpp"
#include "../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../L1_Composition/Context/DeviceDriversContext.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L2_Applications/ApplicationsTask.hpp"
#include "../L4_DomainModels/I2c/Displays/Displays.hpp"
#include "../L5_DeviceModels/Ws28xx/Ws28xxModel.hpp"
#include "../L5_DeviceModels/I2c/I2cModel.hpp"
#include "../L5_DeviceModels/Mcp23017/Mcp23017Model.hpp"
#include "../L5_DeviceModels/Lcd2004/Lcd2004Model.hpp"
#include "../L5_DeviceModels/Tm1637/Tm1637Model.hpp"
#include "../L6_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include "../L6_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../L6_DeviceDrivers/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../L6_DeviceDrivers/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../L6_DeviceDrivers/Tm1637/Tm1637DeviceDriver.hpp"

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
    CreateLinks();
    InitializeDeviceModels();
    InitializeDevicesDrivers();
    InitializeTasks();
    StartTasks();
}

void Orchestrator::CreateLinks()
{
    auto& deviceModels = _context->GetDeviceModels();
    _context->GetDomainModels().GetDisplays().SetDeviceModelsContext(_context->GetDeviceModels());
    deviceModels.GetLcd2004Model().SetI2cModel(deviceModels.GetI2cModel());
    deviceModels.GetMcp23017Model().SetI2cModel(deviceModels.GetI2cModel());

    LinkDeviceModelsToDeviceDrivers();
}

void Orchestrator::LinkDeviceModelsToDeviceDrivers()
{
    auto& ws28xxDeviceDriver = _context->GetDeviceDrivers().GetWs28xxDeviceDriver();
    auto& i2cDeviceDriver = _context->GetDeviceDrivers().GetI2cDeviceDriver();
    auto& mcp23017DeviceDriver = _context->GetDeviceDrivers().GetMcp23017DeviceDriver();
    auto& lcd2004DeviceDriver = _context->GetDeviceDrivers().GetLcd2004DeviceDriver();
    auto& tm1637DeviceDriverCentralPanel = _context->GetDeviceDrivers().GetTm1637DeviceDriverCentralPanel();
    auto& tm1637DeviceDriverPlayer1 = _context->GetDeviceDrivers().GetTm1637DeviceDriverPlayer1();
    auto& tm1637DeviceDriverPlayer2 = _context->GetDeviceDrivers().GetTm1637DeviceDriverPlayer2();

    ws28xxDeviceDriver.SetDeviceModel(_context->GetDeviceModels().GetLedStripModel());
    i2cDeviceDriver.SetDeviceModel(_context->GetDeviceModels().GetI2cModel());
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
    auto& i2cModel = deviceModels.GetI2cModel();
    auto& mcp23017Model = deviceModels.GetMcp23017Model();
    auto& lcd2004Model = deviceModels.GetLcd2004Model();
    auto& tm1637ModelCentralPanel = deviceModels.GetTm1637ModelCentralPanel();
    auto& tm1637ModelPlayer1 = deviceModels.GetTm1637ModelPlayer1();
    auto& tm1637ModelPlayer2 = deviceModels.GetTm1637ModelPlayer2();

    ws28xxModel.Initialize();
    i2cModel.Initialize();
    mcp23017Model.Initialize();
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
