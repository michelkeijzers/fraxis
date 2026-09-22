#include "Builder.hpp"
#include "../../M00_System/I2cTask.hpp"
#include "../../M00_System/NvsTask.hpp"
#include "../../M00_System/LedStripsTask.hpp"
#include "../../M00_System/DiagnosticsTask.hpp"
#include "../../M00_System/Queues/DiagnosticsQueueWriter.hpp"
#include "../../M20_Applications/ApplicationsTask.hpp"
#include "../../M30_Messages/I2cInputQueue.hpp"
#include "../../M30_Messages/I2cOutputQueue.hpp"
#include "../../M30_Messages/LedStripsQueue.hpp"
#include "../../M30_Messages/DiagnosticsQueue.hpp"
#include "../../M30_Messages/NvsQueue.hpp"
#include "../../M40_DomainModels/I2c/Displays/Tm1637/Tm1637.hpp"
#include "../../M40_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../../M50_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../M50_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../../M80_Services/Rtos/Rtos.hpp"

Builder::Builder(Context& context) 
: _context(context) 
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
        std::make_unique<Lcd2004>(),
        std::make_unique<Tm1637>(),
        std::make_unique<Tm1637>(),
        std::make_unique<Tm1637>(),
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
    auto diagnosticsQueue = std::make_unique<DiagnosticsQueue>();
    auto nvsQueue = std::make_unique<NvsQueue>();

    auto inputRtosQueue  = _context.GetServices().GetRtos().CreateQueue(
        I2cInputQueue::MESSAGE_QUEUE_LENGTH, I2cInputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto outputRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        I2cOutputQueue::MESSAGE_QUEUE_LENGTH, I2cOutputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto ledStripsRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        LedStripsQueue::MESSAGE_QUEUE_LENGTH, LedStripsQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto diagnosticsRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        DiagnosticsQueue::MESSAGE_QUEUE_LENGTH, DiagnosticsQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto nvsRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        NvsQueue::MESSAGE_QUEUE_LENGTH, NvsQueue::MESSAGE_QUEUE_ITEM_SIZE);

    i2cInputQueue->SetRtosQueue(*inputRtosQueue);
    i2cOutputQueue->SetRtosQueue(*outputRtosQueue);
    ledStripsQueue->SetRtosQueue(*ledStripsRtosQueue);
    diagnosticsQueue->SetRtosQueue(*diagnosticsRtosQueue);
    nvsQueue->SetRtosQueue(*nvsRtosQueue);

    auto diagnosticsQueueWriter = std::make_unique<DiagnosticsQueueWriter>(*diagnosticsQueue);

    _context.GetQueues().Set(
        std::move(i2cInputQueue),
        std::move(i2cOutputQueue),
        std::move(ledStripsQueue),
        std::move(diagnosticsQueue),
        std::move(diagnosticsQueueWriter),
        std::move(nvsQueue)
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

    auto diagnosticsTask = std::make_unique<DiagnosticsTask>(_context);
    auto& diagnosticsTaskRef = *diagnosticsTask;
    RtosTask* diagnosticsRtosTask = _context.GetServices().GetRtos().CreateTask(
        DiagnosticsTask::TaskEntry, "DiagnosticsTask", 4096, 3, 1, // Stack size 4096, priority 3, core 1
        diagnosticsTask.get()); 
    diagnosticsTaskRef.SetRtosTask(*diagnosticsRtosTask);

    auto nvsTask = std::make_unique<NvsTask>(_context);
    auto& nvsTaskRef = *nvsTask;
    RtosTask* nvsRtosTask = _context.GetServices().GetRtos().CreateTask(
        NvsTask::TaskEntry, "NvsTask", 4096, 3, 1, // Stack size 4096, priority 3, core 1
        nvsTask.get()); 
    nvsTaskRef.SetRtosTask(*nvsRtosTask);

    _context.GetTasks().Set(
        std::move(applicationsTask),
        std::move(i2cTask),
        std::move(ledStripsTask),
        std::move(diagnosticsTask),
        std::move(nvsTask));
}
