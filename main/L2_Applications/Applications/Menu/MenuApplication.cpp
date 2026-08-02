#include "MenuApplication.hpp"
#include "../../ApplicationsManager.hpp"
#include "../../../L3_Messages/Types.hpp"
#include "../../../L9_Utilities/Log/Log.hpp"
/// @todo: Only for windows: remove
#include "../../../L1_Composition/Context/Context.hpp"
#include "../../../L8_Services/Random/Random.hpp"

MenuApplication::MenuApplication(
    Context& context, 
    ApplicationsManager& applicationsManager) 
:   Application(context, applicationsManager), 
    _states(), 
    _renderer(_states),
    // Only for windows @TODO: Remove
    _random(context.GetServices().GetRandom())
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

#ifndef ESP_PLATFORM
    /// @todo: Temporary code
    RunSimulatedDisplay();
#endif

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

#ifndef ESP_PLATFORM

/// @todo: Temporary code

static uint32_t step = 0;
static uint32_t cpTime = 0;
static uint32_t player1 = 0;
static uint32_t player2 = 100000;


void MenuApplication::RunSimulatedDisplay()
{
    step++;
    if (step % 1000 == 0)
    {
        Log::Int("L2 MenuApplication::RunSimulatedDisplay", cpTime);
        cpTime = (cpTime + 24 * 60 - 1) % (24 * 60);
        _send.Time(Types::ETm1637Id::CentralPanel, cpTime / 60, cpTime % 60); // @todo: Temporary for testing

    }

    if (step % 16 == 0)
    {
        for (uint8_t x = 0; x < 72; x++)
        {
            for (uint8_t y = 0; y < 5; y++)
            {
                _send.Pixel(x, y,
                    _random.GetNext() % 255, _random.GetNext() % 255, _random.GetNext() % 255);
            }
        }
        _send.FrameReady();
    }

    player1++;
    player2 += 13;
    _send.Value(Types::ETm1637Id::Player1, player1); // @todo: Temporary for testing
    _send.Value(Types::ETm1637Id::Player2, player2); // @todo: Temporary for testing
    _send.Led(Types::ELedId::Player1, true);
    Render(true);
}

#endif // not ESP_PLATFORM