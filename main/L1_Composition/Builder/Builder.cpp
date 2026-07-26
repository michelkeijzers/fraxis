#include "Builder.hpp"

#include "../../L0_System/LedStripsTask.hpp"
#include "../../L0_System/I2cTask.hpp"
#include "../../L2_Applications/ApplicationsTask.hpp"
#include "../../L3_Messages/LedStripsQueue.hpp"
#include "../../L3_Messages/InputQueue.hpp"
#include "../../L3_Messages/OutputQueue.hpp"
#include "../../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../../L4_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../L4_DomainModels/I2c/Displays/Displays.hpp"
#include "../../L5_DeviceModels/Ws28xx/Ws28xxModel.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017Model.hpp"
#include "../../L5_DeviceModels/Lcd2004/Lcd2004Model.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637Model.hpp"

#include "../../L8_Services/Rtos/Rtos.hpp"

Builder::Builder(Context& context) 
: _context(context) 
{
}

Builder::~Builder() = default;

Context& Builder::GetContext() 
{
    return _context; 
}

void Builder::Build()
{
    BuildDomainModelsContext();
    BuildDeviceModelsContext();
    BuildDeviceDriversContext();
    BuildServicesContext();
    BuildQueues();
    BuildTasks();
}

void Builder::BuildDomainModelsContext()
{
    _context.GetDomainModels().Set(
        std::make_unique<LedStrips>(),
        std::make_unique<IoPins>(),
        std::make_unique<Displays>()
    );
}

void Builder::BuildDeviceModelsContext()
{
    _context.GetDeviceModels().Set(
        std::make_unique<Ws28xxModel>(),
        std::make_unique<Mcp23017Model>(),
        std::make_unique<Lcd2004Model>(),
        std::make_unique<Tm1637Model>(),
        std::make_unique<Tm1637Model>(),
        std::make_unique<Tm1637Model>()
    );
}

void Builder::BuildQueues()
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

void Builder::BuildTasks()
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
