#include "AutoRun.hpp"
#include "../../../IoStates/IoStates.hpp"

AutoRun::AutoRun(Context& context, ApplicationsManager& applicationsManager) 
:   Application(context, applicationsManager) 
{
}

void AutoRun::Start()
{

}

void AutoRun::Pause()
{

}

void AutoRun::Resume()
{

}

void AutoRun::Stop()
{

}

void AutoRun::OnJoystickDirectionChanged(IoStates::EJoystickId id, JoystickState::EDirection direction)
{
    // No actions required
}

void AutoRun::OnJoystickButtonChanged(IoStates::EJoystickId id, bool state)
{
    // No actions required
}

void AutoRun::OnSystemButtonChanged(bool state)
{
    // No actions required
}
