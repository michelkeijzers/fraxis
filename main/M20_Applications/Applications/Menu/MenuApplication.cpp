#include "MenuApplication.hpp"
#include "../../ApplicationsManager.hpp"
#include "../../../M10_Composition/Context/Context.hpp"
#include "../../../M30_Messages/Types.hpp"
#include "../../../M60_DeviceDrivers/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../../../M90_Utilities/Log/Log.hpp"

MenuApplication::MenuApplication(
    Context& context, 
    ApplicationsManager& applicationsManager) 
:   
    Application(context, applicationsManager), 
    _applicationsManager(applicationsManager),
    _states(context.GetServices().GetRandom(), applicationsManager), 
    _renderer(applicationsManager, _states)
{
    _renderer.Render();
    Render(true); // Always render
}

std::string_view MenuApplication::GetName() const
{
    return NAME;
}

IApplication::EType MenuApplication::GetType() const
{
    return IApplication::EType::Menu;
}

std::span<const IApplication::ETag> MenuApplication::GetTags() const
{
    return {};
}

void MenuApplication::Start()
{
    // TO BE IMPLEMENTED
    Resume();
}

void MenuApplication::Pause()
{
    // TO BE IMPLEMENTED
}

void MenuApplication::Resume()
{
    // TO BE IMPLEMENTED
    Send& send = GetSend();
    send.PredefinedCharacter(0, (uint8_t) Lcd2004DeviceDriver::EPredefinedCharacters::TriangleUp);
    send.PredefinedCharacter(0, (uint8_t) Lcd2004DeviceDriver::EPredefinedCharacters::TriangleDown);
}

void MenuApplication::Stop()
{
    // TO BE IMPLEMENTED
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
        if (_applicationsManager.GetApplications().empty() ||
            (this != &_applicationsManager.GetActiveApplication())) // Menu
        {
            return;
        }

        std::array<std::string, Renderer::NR_OF_LINES> result = _renderer.GetCurrentResult();
        Send& send = GetSend();
        for (uint8_t index = 0; index < Renderer::NR_OF_LINES; index++)
        {
            send.Line(index, result[index]);
        }
    }
}
