#include "ComponentsBuilder.hpp"

#include "../../L2_Applications/ApplicationsTask.hpp"

#include "../../L3_Messages/LedStripsQueue.hpp"
#include "../../L3_Messages/InputQueue.hpp"
#include "../../L3_Messages/OutputQueue.hpp"

#include "../../L4_DomainModels/LedStrips/LedStripsTask.hpp"
#include "../../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../../L4_DomainModels/I2c/I2cTask.hpp"
#include "../../L4_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../L4_DomainModels/I2c/Displays/Displays.hpp"

#include "../../L5_DeviceModels/Ws28xx/Ws28xxModel.hpp"
#include "../../L5_DeviceModels/I2c/I2cModel.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017Model.hpp"
#include "../../L5_DeviceModels/Lcd2004/Lcd2004Model.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637Model.hpp"

#include "../../L8_Services/Rtos/Rtos.hpp"

ComponentsBuilder::ComponentsBuilder(Context& context) 
: _context(context) 
{
}

ComponentsBuilder::~ComponentsBuilder() = default;

Context& ComponentsBuilder::GetContext() 
{
    return _context; 
}

void ComponentsBuilder::Build(Context& context)
{
    BuildDomainModelsContext();
    BuildDeviceModelsContext();
    BuildDeviceDriversContext();
    BuildServicesContext();
    BuildQueues();
    BuildTasks();

    CreateLinks();
}

void ComponentsBuilder::BuildDomainModelsContext()
{
    _context.GetDomainModels().Set(
        std::make_unique<LedStrips>(),
        std::make_unique<IoPins>(),
        std::make_unique<Displays>()
    );
}

void ComponentsBuilder::BuildDeviceModelsContext()
{
    _context.GetDeviceModels().Set(
        std::make_unique<Ws28xxModel>(),
        std::make_unique<I2cModel>(),
        std::make_unique<Mcp23017Model>(),
        std::make_unique<Lcd2004Model>(),
        std::make_unique<Tm1637Model>(),
        std::make_unique<Tm1637Model>(),
        std::make_unique<Tm1637Model>()
    );
}

void ComponentsBuilder::BuildQueues()
{
    auto ledStripsQueue = std::make_unique<LedStripsQueue>();
    RtosQueue* ledStripsRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        10, 10);
    ledStripsQueue->SetRtosQueue(*ledStripsRtosQueue);

    auto inputQueue = std::make_unique<InputQueue>();
    RtosQueue* inputRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        10, 10);
    inputQueue->SetRtosQueue(*inputRtosQueue);

    auto outputQueue = std::make_unique<OutputQueue>();
    RtosQueue* outputRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        10, 10);
    outputQueue->SetRtosQueue(*outputRtosQueue);

    _context.GetQueues().Set(
        std::make_unique<LedStripsQueue>(),
        std::make_unique<InputQueue>(),
        std::make_unique<OutputQueue>());
}

void ComponentsBuilder::BuildTasks()
{
    auto applicationsTask = std::make_unique<ApplicationsTask>(_context);
    RtosTask* applicationsRtosTask = _context.GetServices().GetRtos().CreateTask(
        ApplicationsTask::TaskEntry, "ApplicationsTask", 4096, 3, 1, // Stack size 4096, priority 3, core 1
        applicationsTask.get()); 
    applicationsTask->SetRtosTask(*applicationsRtosTask);

    auto i2cTask = std::make_unique<I2cTask>(_context);
    RtosTask* i2cRtosTask = _context.GetServices().GetRtos().CreateTask(
        I2cTask::TaskEntry, "I2cTask", 4096, 3, 1, // Stack size 4096, priority 3, core 1
        i2cTask.get()); 
    i2cTask->SetRtosTask(*i2cRtosTask);

    auto ledStripsTask = std::make_unique<LedStripsTask>(_context);
    RtosTask* ledStripsRtosTask = _context.GetServices().GetRtos().CreateTask(
        LedStripsTask::TaskEntry, "LedStripsTask", 4096, 3, 1, // Stack size 4096, priority 3, core 1
        ledStripsTask.get()); 
    ledStripsTask->SetRtosTask(*ledStripsRtosTask);

    _context.GetTasks().Set(
        std::move(applicationsTask),
        std::move(i2cTask),
        std::move(ledStripsTask));
}

void ComponentsBuilder::CreateLinks()
{
    auto& deviceModels = _context.GetDeviceModels();
    _context.GetDomainModels().GetDisplays().SetDeviceModelsContext(_context.GetDeviceModels());
    deviceModels.GetLcd2004Model().SetI2cModel(deviceModels.GetI2cModel());
    deviceModels.GetMcp23017Model().SetI2cModel(deviceModels.GetI2cModel());
}