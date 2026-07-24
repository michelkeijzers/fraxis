#include "MenuApplication.hpp"

MenuApplication::MenuApplication(Context& context, ApplicationsManager& applicationsManager) 
:   Application(context, applicationsManager) 
{
}

void MenuApplication::Start()
{

}

void MenuApplication::Pause()
{

}


void MenuApplication::Resume()
{

}

void MenuApplication::Stop()
{

}

void MenuApplication::OnJoystickDirectionChanged(IoStates::EJoystickId id, JoystickState::EDirection direction)
{
    // No actions required
}

void MenuApplication::OnJoystickButtonChanged(IoStates::EJoystickId id, bool state)
{
    // No actions required
}

void MenuApplication::OnSystemButtonChanged(bool state)
{
    // No actions required
}
