#include "MenuApplication.hpp"
#include "../../ApplicationsManager.hpp"
#include "../../../L3_Messages/Types.hpp"
#include "../../../L9_Utilities/Log/Log.hpp"
/// TO DOI: Only for windows: remove
#include "../../../L1_Composition/Context/Context.hpp"
#include "../../../L8_Services/Random/Random.hpp"

MenuApplication::MenuApplication(
    Context& context, 
    ApplicationsManager& applicationsManager) 
:   Application(context, applicationsManager), 
    _states(), 
    _renderer(_states),
    // Only for windows TO DO LATER: Remove
    _random(context.GetServices().GetRandom())
{
    _renderer.Render();
    Render(true); // Always render
}

void MenuApplication::Start()
{
    // TO BE IMPLEMENTED
}

void MenuApplication::Pause()
{
    // TO BE IMPLEMENTED
}

void MenuApplication::Resume()
{
    // TO BE IMPLEMENTED
}

void MenuApplication::Stop()
{
    // TO BE IMPLEMENTED
}

void MenuApplication::Run()
{
    bool changed = _states.OnTimePassed();

#ifndef ESP_PLATFORM
    /// TO DO LATER: Temporary code
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
        _send.Line(0, result.line1);
        _send.Line(1, result.line2);

    }
}

#ifndef ESP_PLATFORM

/// TO DO: Temporary code

static uint32_t step = 0; // NOSONAR: not const
static uint32_t cpTime = 0; // NOSONAR: not const
static uint32_t player1 = 0; // NOSONAR: not const
static uint32_t player2 = 100000; // NOSONAR: not const

void MenuApplication::RunSimulatedDisplay()
{
    step++;
    if (step % 1000 == 0)
    {
        cpTime = (cpTime + 24 * 60 - 1) % (24 * 60);
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
    _send.Value(Types::ETm1637Id::Player1, player1);
    _send.Value(Types::ETm1637Id::Player2, player2);
    _send.Time(Types::ETm1637Id::CentralPanel, (uint16_t) player1 / 100 / 60, (player1 / 100) % 60);
    _send.Led(Types::ELedId::Player1, true);
    if (step % 100 == 0)
    {
        //_send.Line(0, "01234567890123456789");
       // _send.Line(1, "ABCDE56789012345689E");
        _send.Line(2, "FGHIJ56789012345689J");
        _send.Line(3, "KLMNOP6789012345689Z");
    }
    Render();
}

#endif // not ESP_PLATFORM
