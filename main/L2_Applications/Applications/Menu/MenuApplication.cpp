#include "MenuApplication.hpp"
#include "../../ApplicationsManager.hpp"
#include "../../../L4_DomainModels/I2c/IoPins/Joystick.hpp"

MenuApplication::MenuApplication(Context& context, ApplicationsManager& applicationsManager) 
:   Application(context, applicationsManager), _states(), _renderer(_states)
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

void MenuApplication::Run()
{
    if (_states.OnTimePassed())
    {
        Render();
    }
}

void MenuApplication::OnJoystickDirectionChanged(IoStates::EJoystickId id, Joystick::EDirection direction)
{
    if (direction != Joystick::EDirection::Centered)
    {
        _states.OnJoystickDirectionChanged(direction);
        Render();
    }
}

void MenuApplication::OnJoystickButtonChanged(IoStates::EJoystickId id, bool state)
{
    if (state)
    {
        _states.OnJoystickButtonPressed();
        Render();
    }
}

void MenuApplication::OnSystemButtonChanged(bool state)
{
    if (state)
    {
        _states.OnSystemButtonPressed();
        Render();
    }
}

void MenuApplication::Render()
{
    _renderer.Render();
    if (_renderer.IsDirty())
    {
        Renderer::Result result = _renderer.GetCurrentResult();
        GetApplicationsManager().GetQueueWriters();
        _send.Line(0, result.line1.data());
        _send.Line(1, result.line2.data());
    }
}
