#include "ApplicationsManager.hpp"
#include "ApplicationsTask.hpp"
#include "Queues/QueueWriters.hpp"
#include "Applications/Menu/MenuApplication.hpp"
#include "Applications/Demos/AutoRun/AutoRun.hpp"
#include "../L3_Messages/Types.hpp"
#include "../L8_Services/Rtos/Rtos.hpp"
#include "../L8_Services/RtosQueue/RtosQueue.hpp"
#include "../L8_Services/RtosTask/RtosTask.hpp"
#include "../L9_Utilities/Log/Log.hpp"

ApplicationsManager::ApplicationsManager(
    ApplicationsTask& applicationsTask, Context& context)
:   _applicationsTask(applicationsTask), 
    _context(context), 
    _queueWriters(nullptr), 
    _ioStates(), 
    _applications(), 
    _activeApplicationIndex(0), 
    _resumedApplicationIndex(0)
{
}

ApplicationsManager::~ApplicationsManager()
{
}

QueueWriters& ApplicationsManager::GetQueueWriters()
{
     return *_queueWriters; 
}

void ApplicationsManager::SetQueueWriters(
    QueueWriters& queueWriters)
{
    _queueWriters = &queueWriters;
}

void ApplicationsManager::AddApplications()
{
    MenuApplication menuApplication(
        _context, *this);
    _applications.push_back(std::make_unique<MenuApplication>(_context, *this));

    AutoRun autoRun(_context, *this);
    _applications.push_back(std::make_unique<AutoRun>(_context, *this));
}

void ApplicationsManager::OnJoystickDirectionChanged(
    Types::EJoystickId id, 
    Types::EJoystickDirection direction)
{
    _ioStates.GetJoystickState(id).SetDirection(direction); 
    GetActiveApplication().OnJoystickDirectionChanged(id, direction);
}

void ApplicationsManager::OnJoystickButtonChanged(
    Types::EJoystickId id, 
    bool state) 
{
    _ioStates.GetJoystickState(id).SetButtonState(state);
    GetActiveApplication().OnJoystickButtonChanged(id, state);    
}

void ApplicationsManager::OnSystemButtonChanged(
    bool state) 
{
    _ioStates.GetSystemButtonState().SetState(state);
    GetActiveApplication().OnSystemButtonChanged(state);
}

void ApplicationsManager::Run()
{
    GetActiveApplication().Run();
}

IoStates& ApplicationsManager::GetIoStates() 
{
    return _ioStates; 
}

std::vector<std::unique_ptr<Application>>& ApplicationsManager::GetApplications()
{
    return _applications;
}

uint16_t ApplicationsManager::GetActiveApplicationIndex()
{
    return _activeApplicationIndex;
}

Application& ApplicationsManager::GetActiveApplication()
{
    return *(_applications[_activeApplicationIndex]);
}

void ApplicationsManager::SetActiveApplicationIndex(
    uint16_t applicationIndex)
{
    _activeApplicationIndex = applicationIndex;
}

uint16_t ApplicationsManager::GetResumedApplicationIndex()
{
    return _resumedApplicationIndex;
}

void ApplicationsManager::SetResumedApplicationIndex(
    uint16_t applicationIndex)
{
    _resumedApplicationIndex = applicationIndex;
}
