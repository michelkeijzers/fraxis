#include "MenuApplication.hpp"

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

void MenuApplication::OnJoystickDirectionChanged(IoStates::EJoystickId id, JoystickState::EDirection direction)
{
    if (direction != JoystickState::EDirection::Centered)
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

void MenuApplication::OnTimePassed()
{
    if (_states.OnTimePassed())
    {
        Render();
    }
}

void MenuApplication::Render()
{
    _renderer.Render();
    if (_renderer.IsDirty())
    {
        Renderer::Result result = _renderer.GetCurrentResult();

        //TODO _context.GetDomainModels().lcd2004Display.WriteLines(result.line1.data(), result.line2.data());
    }
}