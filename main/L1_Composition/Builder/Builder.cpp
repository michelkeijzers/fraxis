#include "Builder.hpp"

#include "../../L0_System/LedStripsTask.hpp"
#include "../../L0_System/I2cTask.hpp"
#include "../../L2_Applications/ApplicationsTask.hpp"
#include "../../L3_Messages/I2cInputQueue.hpp"
#include "../../L3_Messages/I2cOutputQueue.hpp"
#include "../../L3_Messages/LedStripsQueue.hpp"
#include "../../L4_DomainModels/I2c/Displays/Displays.hpp"
#include "../../L4_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../../L8_Services/Rtos/Rtos.hpp"

Builder::Builder(Context& context) 
: _context(context) 
{
}

Builder::~Builder()
{
}

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
        std::make_unique<Displays>(),
        std::make_unique<IoPins>(),
        std::make_unique<LedStrips>()
    );
}

void Builder::BuildDeviceModelsContext()
{
    _context.GetDeviceModels().Set(
        std::make_unique<Lcd2004DeviceModel>(),
        std::make_unique<Mcp23017DeviceModel>(),
        std::make_unique<Tm1637DeviceModel>(),
        std::make_unique<Tm1637DeviceModel>(),
        std::make_unique<Tm1637DeviceModel>(),
        std::make_unique<Ws28xxDeviceModel>()
    );
}

void Builder::BuildDeviceDriversContext()
{
    GetContext().GetDeviceDrivers().Set(
        std::make_unique<I2cDeviceDriver>(),
        std::make_unique<Lcd2004DeviceDriver>(),
        std::make_unique<Mcp23017DeviceDriver>(),
        std::make_unique<Tm1637DeviceDriver>(),
        std::make_unique<Tm1637DeviceDriver>(),
        std::make_unique<Tm1637DeviceDriver>(),
        std::make_unique<Ws28xxDeviceDriver>()
    );
}

void Builder::BuildQueues()
{
    auto i2cInputQueue = std::make_unique<I2cInputQueue>();
    auto i2cOutputQueue = std::make_unique<I2cOutputQueue>();
    auto ledStripsQueue = std::make_unique<LedStripsQueue>();

    auto inputRtosQueue  = _context.GetServices().GetRtos().CreateQueue(
        I2cInputQueue::MESSAGE_QUEUE_LENGTH, I2cInputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto outputRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        I2cOutputQueue::MESSAGE_QUEUE_LENGTH, I2cOutputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto ledStripsRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        LedStripsQueue::MESSAGE_QUEUE_LENGTH, LedStripsQueue::MESSAGE_QUEUE_ITEM_SIZE);

    i2cInputQueue->SetRtosQueue(*inputRtosQueue);
    i2cOutputQueue->SetRtosQueue(*outputRtosQueue);
    ledStripsQueue->SetRtosQueue(*ledStripsRtosQueue);

    _context.GetQueues().Set(
        std::move(i2cInputQueue),
        std::move(i2cOutputQueue),
        std::move(ledStripsQueue)
    );
}

void Builder::BuildTasks()
{
    auto applicationsTask = std::make_unique<ApplicationsTask>(_context);
    auto& applicationsTaskRef = *applicationsTask;
    RtosTask* applicationsRtosTask = _context.GetServices().GetRtos().CreateTask(
        ApplicationsTask::TaskEntry, "ApplicationsTask", 4096, 3, 1, // Stack size 4096, priority 3, core 1
        applicationsTask.get()); 
    applicationsTaskRef.SetRtosTask(*applicationsRtosTask);

    auto i2cTask = std::make_unique<I2cTask>(_context);
    auto& i2cTaskRef = *i2cTask;
    RtosTask* i2cRtosTask = _context.GetServices().GetRtos().CreateTask(
        I2cTask::TaskEntry, "I2cTask", 4096, 3, 1, // Stack size 4096, priority 3, core 1
        i2cTask.get()); 
    i2cTaskRef.SetRtosTask(*i2cRtosTask);

    auto ledStripsTask = std::make_unique<LedStripsTask>(_context);
    auto& ledStripsTaskRef = *ledStripsTask;
    RtosTask* ledStripsRtosTask = _context.GetServices().GetRtos().CreateTask(
        LedStripsTask::TaskEntry, "LedStripsTask", 4096, 3, 1, // Stack size 4096, priority 3, core 1
        ledStripsTask.get()); 
    ledStripsTaskRef.SetRtosTask(*ledStripsRtosTask);

    _context.GetTasks().Set(
        std::move(applicationsTask),
        std::move(i2cTask),
        std::move(ledStripsTask));
}
