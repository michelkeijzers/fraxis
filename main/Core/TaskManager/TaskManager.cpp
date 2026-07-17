#include "TaskManager.hpp"

#include "../../Common/Components/LedStrip/LedStripDriver.hpp"
#include "../../Common/Services/Rtos/Rtos.hpp"
#include "../../Common/Services/RtosQueue/RtosQueue.hpp"
#include "../../Common/Services/RtosTask/RtosTask.hpp"
#include "../../Common/Services/Debug/Debug.hpp"

#include "../../Tasks/Messages/Message.hpp"
#include "../../Tasks/SystemTask/SystemTask.hpp"
#include "../../Tasks/LedStripsTask/LedStripsTask.hpp"
#include "../../Tasks/I2cTask/I2cTask.hpp"

#include "../Components/LedStrips.hpp"
#include "../../Common/Components/Lcd1602Display/Lcd1602DisplayDriver.hpp"
#include "../../Common/Components/Tm1637/Tm1637Driver.hpp"
#include "../../Core/Components/Mcp23017.hpp"
#include "../Components/PinIo.hpp"
#include "../Components/ComponentsBuilder.hpp"


TaskManager::TaskManager(
    ComponentsBuilder::FraxisComponents& fraxisComponents, 
    ComponentsBuilder::Models& models, 
    ComponentsBuilder::Drivers& drivers)
:   _fraxisComponents(fraxisComponents), _models(models), _drivers(drivers),
    _systemTask(nullptr), _ledStripsTask(nullptr), _i2cTask(nullptr),
    _systemQueue(nullptr), _ledStripsQueue(nullptr), _i2cQueue(nullptr)
{
}

void TaskManager::Initialize()
{
    CreateQueues();
    CreateTasks();

    _fraxisComponents.pinIo->Initialize();

    //_drivers.ledStripDriver->Initialize();
    Message message;
    message.id = Message::EId::LedStrip_Initialize;
    _ledStripsQueue->Send(&message, 0);
            
    message.id = Message::EId::I2c_Initialize;
    _i2cQueue->Send(&message, 0);

    message.id = Message::EId::Lcd1602Display_Initialize;
    _i2cQueue->Send(&message, 0);

    message.id = Message::EId::Tm1637_Initialize;
    message.tm1637_Initialize_Parameters.id = Message::ETm1637Id::CentralPanel;
    _i2cQueue->Send(&message, 0);

    message.id = Message::EId::Tm1637_Initialize;
    message.tm1637_Initialize_Parameters.id = Message::ETm1637Id::Player1;
    _i2cQueue->Send(&message, 0);

    message.id = Message::EId::Tm1637_Initialize;
    message.tm1637_Initialize_Parameters.id = Message::ETm1637Id::Player2;
    _i2cQueue->Send(&message, 0);

    //TODO to be done by messages
    //_drivers.lcd1602DisplayDriver->Initialize();

    //_drivers.i2c.Initialize();
    _drivers.mcp23017->Initialize();
}

void TaskManager::Run(bool keepRunning)
{
    StartTasks();
}

void TaskManager::CreateQueues()
{
    _systemQueue = _drivers.rtos->CreateQueue(10, sizeof(int)); //  TODO: Max size
    _ledStripsQueue = _drivers.rtos->CreateQueue(10, sizeof(int));
    _i2cQueue = _drivers.rtos->CreateQueue(10, sizeof(int));
}

void TaskManager::CreateTasks()
{
    _systemTask = new SystemTask(nullptr, _ledStripsQueue, _i2cQueue,
        _fraxisComponents, _models, _drivers); // TODO: Remove nullptr
    _ledStripsTask = new LedStripsTask(nullptr, *_ledStripsQueue, _fraxisComponents, _models, _drivers);
    _i2cTask = new I2cTask(nullptr, *_i2cQueue, _fraxisComponents, _models, _drivers);

    RtosTask* systemTask    = _drivers.rtos->CreateTask(
        SystemTaskFunction, "SystemTask", 4096, 3, 1, _systemTask); // Stack size 4096, priority 3, core 1
    RtosTask* ledStripsTask = _drivers.rtos->CreateTask(
        LedStripsTaskFunction, "LedStripsTask", 4096, 4, 0, _ledStripsTask); // Stack size 4096, priority 4, core 0
    RtosTask* i2cTask = _drivers.rtos->CreateTask(
        I2cTaskFunction, "I2cTask", 4096, 4, 0, _i2cTask); // Stack size 4096, priority 4, core 0

    _systemTask->SetRtosTask(systemTask);
    _ledStripsTask->SetRtosTask(ledStripsTask);
    _i2cTask->SetRtosTask(i2cTask);
}

void TaskManager::StartTasks()
{
    _systemTask->GetRtosTask()->Start();
    _ledStripsTask->GetRtosTask()->Start();
    _i2cTask->GetRtosTask()->Start();
}

void TaskManager::SystemTaskFunction(void* param)
{
    SystemTask* systemTask = static_cast<SystemTask*>(param);
    systemTask->Run();
}

void TaskManager::LedStripsTaskFunction(void* param)
{
    LedStripsTask* ledStripTask = static_cast<LedStripsTask*>(param);
    ledStripTask->Run();
}

void TaskManager::I2cTaskFunction(void* param)
{
    I2cTask* i2cTask = static_cast<I2cTask*>(param);
    i2cTask->Run();
}
