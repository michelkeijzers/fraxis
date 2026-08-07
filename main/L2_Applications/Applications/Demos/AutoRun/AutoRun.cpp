#include "AutoRun.hpp"
#include "../../../../L2_Applications/ApplicationsManager.hpp"
#include "../../../../L3_Messages/Types.hpp"

AutoRun::AutoRun(
    Context& context, 
    ApplicationsManager& applicationsManager) 
:   Application(context, applicationsManager) 
{
}

void AutoRun::Start()
{
    // TO BE IMPLEMENTED
}

void AutoRun::Pause()
{
    // TO BE IMPLEMENTED
}

void AutoRun::Resume()
{
    // TO BE IMPLEMENTED
}

void AutoRun::Stop()
{
    // TO BE IMPLEMENTED
}

void AutoRun::Run()
{
    GetApplicationsManager().GetQueueWriters();
    GetSend().Value(Types::ETm1637Id::Player1, 50000);
}

void AutoRun::OnJoystickDirectionChanged(
    Types::EJoystickId id, 
    Types::EJoystickDirection direction)
{
    // No actions required
}

void AutoRun::OnJoystickButtonChanged(
    Types::EJoystickId id, 
    bool state)
{
    // No actions required
}

void AutoRun::OnSystemButtonChanged(
    bool state)
{
    // No actions required
}
