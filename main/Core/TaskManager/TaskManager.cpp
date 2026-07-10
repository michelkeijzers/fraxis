#include "TaskManager.hpp"

#include "../../Common/Components/LedStrip/LedStripDriver.hpp"
#include "../../Common/Services/Rtos/Rtos.hpp"
#include "../../Common/Services/RtosTask/RtosTask.hpp"
#include "../../Common/Services/Debug/Debug.hpp"

#include "../../Tasks/SystemTask/SystemTask.hpp"
#include "../../Tasks/LedStripsTask/LedStripsTask.hpp"

#include "../Components/LedStrips.hpp"
#include "../Components/Lcd1602Display.hpp"
#include "../../Core/Components/Mcp23017.hpp"
#include "../Components/PinIo.hpp"
#include "../Components/Tm1637.hpp"

TaskManager::TaskManager(ComponentsBuilder::FraxisComponents& fraxisComponents, ComponentsBuilder::Models& models, 
    ComponentsBuilder::Drivers& drivers)
: _fraxisComponents(fraxisComponents), _models(models), _drivers(drivers), 
  _systemTask(nullptr), _ledStripsTask(nullptr)
{
}

void TaskManager::Initialize()
{
    _fraxisComponents.pinIo->Initialize();

    _drivers.ledStripDriver->Initialize();
    
    //TODO to be done in various tasks
    _drivers.lcdDisplay->Initialize();
    // _drivers.rtosTask->Initialize(); TODO: Create (?) or make rtosTask Service
    //_drivers.i2c.Initialize();
    _drivers.mcp23017->Initialize();
    _drivers.tm1637CentralPanel->Initialize();
    _drivers.tm1637Player1->Initialize();
    _drivers.tm1637Player2->Initialize();
}

void TaskManager::Run(bool keepRunning)
{
    CreateTasks();
}

void TaskManager::CreateTasks()
{
    _systemTask = new SystemTask(nullptr, _fraxisComponents, _drivers);
    _ledStripsTask = new LedStripsTask(nullptr, _fraxisComponents, _models, _drivers);

    RtosTask* systemTask    = _drivers.rtos->CreateTask(
        SystemTaskFunction, "SystemTask", 4096, 3, 1, _systemTask); // Stack size 4096, priority 3, core 1
    RtosTask* ledStripsTask = _drivers.rtos->CreateTask(
        LedStripsTaskFunction, "LedStripsTask", 4096, 4, 0, _ledStripsTask); // Stack size 4096, priority 4, core 0

    _systemTask->SetRtosTask(systemTask);
    _ledStripsTask->SetRtosTask(ledStripsTask);

    systemTask->Start();
    ledStripsTask->Start();

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
