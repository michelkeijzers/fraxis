#include "TaskManager.hpp"

#include "../../Common/Components/LedStrip/LedStripDriver.hpp"
#include "../../Common/Services/Rtos/Rtos.hpp"
#include "../../Common/Services/RtosQueue/RtosQueue.hpp"
#include "../../Common/Services/RtosTask/RtosTask.hpp"
#include "../../Common/Services/Debug/Debug.hpp"

#include "../../Tasks/Messages/Message.hpp"
#include "../../Applications/ApplicationsTask.hpp"
#include "../../Tasks/LedStripsTask/LedStripsTask.hpp"
#include "../../Tasks/I2cTask/I2cTask.hpp"

#include "../Components/LedStrips.hpp"
#include "../../Common/Components/Mcp23017/Mcp23017Driver.hpp"
#include "../../Common/Components/Lcd1602Display/Lcd1602DisplayDriver.hpp"
#include "../../Common/Components/Tm1637/Tm1637Driver.hpp"
#include "../Components/PinIo.hpp"
#include "../Components/ComponentsBuilder.hpp"


TaskManager::TaskManager(
    ComponentsBuilder::FraxisComponents& fraxisComponents, 
    ComponentsBuilder::Models& models, 
    ComponentsBuilder::Drivers& drivers)
:   _fraxisComponents(fraxisComponents), _models(models), _drivers(drivers),
    _applicationsTask(nullptr), _ledStripsTask(nullptr), _i2cTask(nullptr),
    _applicationsQueue(nullptr), _ledStripsQueue(nullptr), _i2cQueue(nullptr)
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

    message.id = Message::EId::Mcp23017_Initialize;
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
    _drivers.mcp23017Driver->Initialize();
}

void TaskManager::Run(bool keepRunning)
{
    StartTasks();
}

void TaskManager::CreateQueues()
{
    _applicationsQueue = _drivers.rtos->CreateQueue(10, sizeof(int)); //  TODO: Max size
    _ledStripsQueue = _drivers.rtos->CreateQueue(10, sizeof(int));
    _i2cQueue = _drivers.rtos->CreateQueue(10, sizeof(int));
}

void TaskManager::CreateTasks()
{
    _applicationsTask = new ApplicationsTask(nullptr, _ledStripsQueue, _i2cQueue,
        _fraxisComponents, _models, _drivers); // TODO: Remove nullptr
    _ledStripsTask = new LedStripsTask(nullptr, *_ledStripsQueue, _fraxisComponents, _models, _drivers);
    _i2cTask = new I2cTask(nullptr, *_i2cQueue, _fraxisComponents, _models, _drivers);

    RtosTask* applicationsTask    = _drivers.rtos->CreateTask(
        ApplicationsTaskFunction, "ApplicationsTask", 4096, 3, 1, _applicationsTask); // Stack size 4096, priority 3, core 1
    RtosTask* ledStripsTask = _drivers.rtos->CreateTask(
        LedStripsTaskFunction, "LedStripsTask", 4096, 4, 0, _ledStripsTask); // Stack size 4096, priority 4, core 0
    RtosTask* i2cTask = _drivers.rtos->CreateTask(
        I2cTaskFunction, "I2cTask", 4096, 4, 0, _i2cTask); // Stack size 4096, priority 4, core 0

    _applicationsTask->SetRtosTask(applicationsTask);
    _ledStripsTask->SetRtosTask(ledStripsTask);
    _i2cTask->SetRtosTask(i2cTask);
}

void TaskManager::StartTasks()
{
    _applicationsTask->GetRtosTask()->Start();
    _ledStripsTask->GetRtosTask()->Start();
    _i2cTask->GetRtosTask()->Start();
}

void TaskManager::ApplicationsTaskFunction(void* param)
{
    ApplicationsTask* applicationsTask = static_cast<ApplicationsTask*>(param);
    applicationsTask->Run();
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
