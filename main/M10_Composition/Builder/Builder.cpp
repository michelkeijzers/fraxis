#include "Builder.hpp"
#include "../../M00_System/I2cTask.hpp"
#include "../../M00_System/SpiTask.hpp"
#include "../../M00_System/LedStripsTask.hpp"
#include "../../M00_System/DiagnosticsTask.hpp"
#include "../../M00_System/AudioTask.hpp"
#include "../../M00_System/Queues/DiagnosticsQueueWriter.hpp"
#include "../../M20_Applications/ApplicationsTask.hpp"
#include "../../M30_Messages/DiagnosticsQueue.hpp"
#include "../../M30_Messages/I2cInputQueue.hpp"
#include "../../M30_Messages/I2cOutputQueue.hpp"
#include "../../M30_Messages/LedStripsQueue.hpp"
#include "../../M30_Messages/SpiInputQueue.hpp"
#include "../../M30_Messages/SpiOutputQueue.hpp"
#include "../../M30_Messages/Audio/AudioInputQueue.hpp"
#include "../../M30_Messages/Audio/AudioOutputQueue.hpp"
#include "../../M40_DomainModels/I2c/Displays/Tm1637/Tm1637.hpp"
#include "../../M40_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../../M40_DomainModels/Spi/MicroSdCard/MicroSdCard.hpp"
#include "../../M40_DomainModels/Audio/Microphone/Inmp1441.hpp"
#include "../../M40_DomainModels/Audio/Dac/Max53987a.hpp"
#include "../../M40_DomainModels/Audio/Buzzer/Buzzer.hpp"
#include "../../M50_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../M50_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../../M50_DeviceModels/Audio/AudioDeviceModel.hpp"
#include "../../M50_DeviceModels/Audio/Microphone/MicrophoneDeviceModel.hpp"
#include "../../M50_DeviceModels/Audio/Dac/DacDeviceModel.hpp"
#include "../../M50_DeviceModels/Audio/Buzzer/BuzzerDeviceModel.hpp"
#include "../../M81_RtosServices/Rtos/Rtos.hpp"

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
        std::make_unique<LedStrips>(),
        std::make_unique<MicroSdCard>(),
        std::make_unique<Inmp1441>(),
        std::make_unique<Max53987a>(),
        std::make_unique<Buzzer>()
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
        std::make_unique<Ws28xxDeviceModel>(),
        std::make_unique<MicroSdCardDeviceModel>(),
        std::make_unique<AudioDeviceModel>(),
        std::make_unique<MicrophoneDeviceModel>(),
        std::make_unique<DacDeviceModel>(),
        std::make_unique<BuzzerDeviceModel>()
    );
}

void Builder::BuildDeviceDriversContext()
{
    GetContext().GetDeviceDrivers().Set(
        std::make_unique<I2cDeviceDriver>(),
        std::make_unique<SpiDeviceDriver>(),
        std::make_unique<Lcd2004DeviceDriver>(),
        std::make_unique<Mcp23017DeviceDriver>(),
        std::make_unique<Tm1637DeviceDriver>(),
        std::make_unique<Tm1637DeviceDriver>(),
        std::make_unique<Tm1637DeviceDriver>(),
        std::make_unique<Ws28xxDeviceDriver>(),
        std::make_unique<MicroSdCardDeviceDriver>(),
        std::make_unique<AudioDeviceDriver>(),
        std::make_unique<Inmp1441DeviceDriver>(),
        std::make_unique<Max53987aDeviceDriver>(),
        std::make_unique<BuzzerDeviceDriver>()
    );
}

void Builder::BuildQueues()
{
    auto i2cInputQueue = std::make_unique<I2cInputQueue>();
    auto i2cOutputQueue = std::make_unique<I2cOutputQueue>();
    auto spiInputQueue = std::make_unique<SpiInputQueue>();
    auto spiOutputQueue = std::make_unique<SpiOutputQueue>();
    auto ledStripsQueue = std::make_unique<LedStripsQueue>();
    auto diagnosticsQueue = std::make_unique<DiagnosticsQueue>();
    auto audioInputQueue = std::make_unique<AudioInputQueue>();
    auto audioOutputQueue = std::make_unique<AudioOutputQueue>();

    auto i2cInputRtosQueue  = _context.GetServices().GetRtos().CreateQueue(
        I2cInputQueue::MESSAGE_QUEUE_LENGTH, I2cInputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto i2cOutputRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        I2cOutputQueue::MESSAGE_QUEUE_LENGTH, I2cOutputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto spiInputRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        SpiInputQueue::MESSAGE_QUEUE_LENGTH, SpiInputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto spiOutputRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        SpiOutputQueue::MESSAGE_QUEUE_LENGTH, SpiOutputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto ledStripsRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        LedStripsQueue::MESSAGE_QUEUE_LENGTH, LedStripsQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto diagnosticsRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        DiagnosticsQueue::MESSAGE_QUEUE_LENGTH, DiagnosticsQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto audioInputRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        AudioInputQueue::MESSAGE_QUEUE_LENGTH, AudioInputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto audioOutputRtosQueue = _context.GetServices().GetRtos().CreateQueue(
        AudioOutputQueue::MESSAGE_QUEUE_LENGTH, AudioOutputQueue::MESSAGE_QUEUE_ITEM_SIZE);

    i2cInputQueue->SetRtosQueue(*i2cInputRtosQueue);
    i2cOutputQueue->SetRtosQueue(*i2cOutputRtosQueue);
    spiInputQueue->SetRtosQueue(*spiInputRtosQueue);
    spiOutputQueue->SetRtosQueue(*spiOutputRtosQueue);
    ledStripsQueue->SetRtosQueue(*ledStripsRtosQueue);
    diagnosticsQueue->SetRtosQueue(*diagnosticsRtosQueue);
    audioInputQueue->SetRtosQueue(*audioInputRtosQueue);
    audioOutputQueue->SetRtosQueue(*audioOutputRtosQueue);

    auto diagnosticsQueueWriter = std::make_unique<DiagnosticsQueueWriter>(*diagnosticsQueue);

    _context.GetQueues().Set(
        std::move(i2cInputQueue),
        std::move(i2cOutputQueue),
        std::move(spiInputQueue),
        std::move(spiOutputQueue),
        std::move(ledStripsQueue),
        std::move(diagnosticsQueue),
        std::move(diagnosticsQueueWriter),
        std::move(audioInputQueue),
        std::move(audioOutputQueue)
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

    auto spiTask = std::make_unique<SpiTask>(_context);
    auto& spiTaskRef = *spiTask;
    RtosTask* spiRtosTask = _context.GetServices().GetRtos().CreateTask(
        SpiTask::TaskEntry, "SpiTask", 4096, 3, 1, // Stack size 4096, priority 3, core 1
        spiTask.get()); 
    spiTaskRef.SetRtosTask(*spiRtosTask);

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

    auto audioTask = std::make_unique<AudioTask>(_context);
    auto& audioTaskRef = *audioTask;
    RtosTask* audioRtosTask = _context.GetServices().GetRtos().CreateTask(
        AudioTask::TaskEntry, "AudioTask", 4096, 3, 1, // Stack size 4096, priority 3, core 1
        audioTask.get()); 
    audioTaskRef.SetRtosTask(*audioRtosTask);

    _context.GetTasks().Set(
        std::move(applicationsTask),
        std::move(i2cTask),
        std::move(spiTask),
        std::move(ledStripsTask),
        std::move(diagnosticsTask),
        std::move(audioTask));
}
