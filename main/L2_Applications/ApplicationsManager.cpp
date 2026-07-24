#include "ApplicationsManager.hpp"
#include "ApplicationsTask.hpp"

#include "Applications/Menu/MenuApplication.hpp"
#include "Applications/Demos/AutoRun/AutoRun.hpp"

#include "../L8_Services/Rtos/Rtos.hpp"
#include "../L8_Services/RtosQueue/RtosQueue.hpp"
#include "../L8_Services/RtosTask/RtosTask.hpp"
#include "../L8_Services/Debug/Debug.hpp"

ApplicationsManager::ApplicationsManager(ApplicationsTask& applicationsTask, Context& context)
: _applicationsTask(applicationsTask), _context(context), _ioStates(), _applications()
{
}

ApplicationsManager::~ApplicationsManager()
{
}

void ApplicationsManager::AddApplications()
{
    MenuApplication menuApplication(_context, *this);
    _applications.push_back(std::make_unique<MenuApplication>(_context, *this));

    AutoRun autoRun(_context, *this);
    _applications.push_back(std::make_unique<AutoRun>(_context, *this));
}

void ApplicationsManager::OnJoystickDirectionChanged(IoStates::EJoystickId id, JoystickState::EDirection direction)
{
    _ioStates.GetJoystickState(id).SetDirection(direction); 
    GetActiveApplication().OnJoystickDirectionChanged(id, direction);
}

void ApplicationsManager::OnJoystickButtonChanged(IoStates::EJoystickId id, bool state) 
{
    _ioStates.GetJoystickState(id).SetButtonState(state);
    GetActiveApplication().OnJoystickButtonChanged(id, state);    
}

void ApplicationsManager::OnSystemButtonChanged(bool state) 
{
    _ioStates.GetSystemButtonState().SetState(state);
    GetActiveApplication().OnSystemButtonChanged(state);
}

uint16_t ApplicationsManager::GetActiveApplicationIndex()
{
    return _activeApplicationIndex;
}

Application& ApplicationsManager::GetActiveApplication()
{
    return *(_applications[_activeApplicationIndex]);
}

void ApplicationsManager::SetActiveApplicationIndex(uint16_t applicationIndex)
{
    _activeApplicationIndex = applicationIndex;
}

uint16_t ApplicationsManager::GetResumedApplicationIndex()
{
    return _resumedApplicationIndex;
}

void ApplicationsManager::SetResumedApplicationIndex(uint16_t applicationIndex)
{
    _resumedApplicationIndex = applicationIndex;
}
