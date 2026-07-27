#include "AutoRun.hpp"
#include "../../../../L3_Messages/Types.hpp"

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


void AutoRun::Run()
{
    //TODO
}

void AutoRun::OnJoystickDirectionChanged(Types::EJoystickId id, Types::EJoystickDirection direction)
{
    // No actions required
}

void AutoRun::OnJoystickButtonChanged(Types::EJoystickId id, bool state)
{
    // No actions required
}

void AutoRun::OnSystemButtonChanged(bool state)
{
    // No actions required
}
