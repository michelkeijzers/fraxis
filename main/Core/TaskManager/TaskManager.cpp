#include "TaskManager.hpp"

#include "../../Common/Components/LedStrip/LedStripDriver.hpp"
#include "../../Common/Services/Rtos/Rtos.hpp"
#include "../../Common/Services/RtosQueue/RtosQueue.hpp"
#include "../../Common/Services/RtosTask/RtosTask.hpp"
#include "../../Common/Services/Debug/Debug.hpp"

#include "../../Tasks/Messages/LedStripMessage.hpp"
#include "../../Tasks/SystemTask/SystemTask.hpp"
#include "../../Tasks/LedStripsTask/LedStripsTask.hpp"

#include "../Components/LedStrips.hpp"
#include "../Components/Lcd1602Display.hpp"
#include "../../Core/Components/Mcp23017.hpp"
#include "../Components/PinIo.hpp"
#include "../Components/Tm1637.hpp"
#include "../Components/ComponentsBuilder.hpp"


TaskManager::TaskManager(ComponentsBuilder::FraxisComponents& fraxisComponents, ComponentsBuilder::Models& models, 
    ComponentsBuilder::Drivers& drivers)
: _fraxisComponents(fraxisComponents), _models(models), _drivers(drivers),
  _systemTask(nullptr), _ledStripsTask(nullptr), _systemQueue(nullptr), _ledStripsQueue(nullptr)
{
}

void TaskManager::Initialize()
{
    CreateQueues();
    CreateTasks();

    _fraxisComponents.pinIo->Initialize();

    //_drivers.ledStripDriver->Initialize();
    LedStripMessage message;
    message.id = LedStripMessage::EId::Initialize;
    message.initializeParameters.numberOfLeds = LedStrips::NUMBER_OF_LEDS;
    message.initializeParameters.dataPin = 13;
    _ledStripsQueue->Send(&message, 10);
    
    //TODO to be done by messages
    _drivers.lcdDisplay->Initialize();
    //_drivers.i2c.Initialize();
    _drivers.mcp23017->Initialize();
    _drivers.tm1637CentralPanel->Initialize();
    _drivers.tm1637Player1->Initialize();
    _drivers.tm1637Player2->Initialize();
}

void TaskManager::Run(bool keepRunning)
{
    StartTasks();
}

void TaskManager::CreateQueues()
{
    _systemQueue = _drivers.rtos->CreateQueue(10, sizeof(int));
    _ledStripsQueue = _drivers.rtos->CreateQueue(10, sizeof(int));
}

void TaskManager::CreateTasks()
{
    _systemTask = new SystemTask(nullptr, _ledStripsQueue, 
        _fraxisComponents, _models, _drivers); // TODO: Remove nullptr
    _ledStripsTask = new LedStripsTask(nullptr, *_ledStripsQueue, _fraxisComponents, _models, _drivers);

    RtosTask* systemTask    = _drivers.rtos->CreateTask(
        SystemTaskFunction, "SystemTask", 4096, 3, 1, _systemTask); // Stack size 4096, priority 3, core 1
    RtosTask* ledStripsTask = _drivers.rtos->CreateTask(
        LedStripsTaskFunction, "LedStripsTask", 4096, 4, 0, _ledStripsTask); // Stack size 4096, priority 4, core 0

    _systemTask->SetRtosTask(systemTask);
    _ledStripsTask->SetRtosTask(ledStripsTask);
}

void TaskManager::StartTasks()
{
    _systemTask->GetRtosTask()->Start();
    _ledStripsTask->GetRtosTask()->Start();
}

void TaskManager::SystemTaskFunction(void* param)
{
    SystemTask* systemTask = static_cast<SystemTask*>(param);
    systemTask->Run();
}

void TaskManager::LedStripsTaskFunction(void* param)
{
    LedStripsTask* ledTask = static_cast<LedStripsTask*>(param);
    ledTask->Run();
}
