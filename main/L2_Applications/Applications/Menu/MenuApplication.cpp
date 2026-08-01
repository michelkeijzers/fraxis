#include "MenuApplication.hpp"
#include "../../ApplicationsManager.hpp"
#include "../../../L3_Messages/Types.hpp"

MenuApplication::MenuApplication(Context& context, ApplicationsManager& applicationsManager) 
:   Application(context, applicationsManager), _states(), _renderer(_states)
{
    _renderer.Render();
    Render(true); // Always render
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
    bool changed = _states.OnTimePassed();
    if (changed || _renderer.IsDirty())
    {
        Render();
    }
}

void MenuApplication::OnJoystickDirectionChanged(Types::EJoystickId id, Types::EJoystickDirection direction)
{
    if (direction != Types::EJoystickDirection::Centered)
    {
        _states.OnJoystickDirectionChanged(direction);
        Render();
    }
}

void MenuApplication::OnJoystickButtonChanged(Types::EJoystickId id, bool state)
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

void MenuApplication::Render(bool alwaysRender)
{
    _renderer.Render();
    if (_renderer.IsDirty() || alwaysRender)
    {
        Renderer::Result result = _renderer.GetCurrentResult();
        GetApplicationsManager().GetQueueWriters();
        _send.Line(0, result.line1.data());
        _send.Line(1, result.line2.data());
    }
}
