#include "AutoRun.hpp"
#include "../../../M10_Composition/Context/Context.hpp"
#include "../../../M20_Applications/ApplicationsManager.hpp"
#include "../../../M30_Messages/Types.hpp"
#include "../../../M80_Services/Random/Random.hpp"
#include "../../../M90_Utilities/Time/TimeUtilities.hpp" 

static constexpr std::array<IApplication::ETag, 3> TAGS =
{
    IApplication::ETag::LedStrips,
    IApplication::ETag::Leds,
    IApplication::ETag::Displays
};

AutoRun::AutoRun(
    Context& context, 
    ApplicationsManager& applicationsManager) 
:   
    Application(context, applicationsManager),
    _random(context.GetServices().GetRandom()),
    _step(0),
    _cpTime(0),
    _player1(0),
    _player2(100000)
{
}

std::string_view AutoRun::GetName() const
{
    return "Auto Run";
}

IApplication::EType AutoRun::GetType() const
{
    return IApplication::EType::Utility;
}

std::span<const IApplication::ETag> AutoRun::GetTags() const
{
    return TAGS;
}

void AutoRun::Run()
{
    if (GetState() != IApplication::EState::Running)
    {
        return;
    }

    GetApplicationsManager().GetQueueWriters();

    Send& send = GetSend();
    send.EnableTm1637(Types::ETm1637Id::CentralPanel, true);
    send.EnableTm1637(Types::ETm1637Id::Player1, true);
    send.EnableTm1637(Types::ETm1637Id::Player2, true);

    send.Value(Types::ETm1637Id::Player1, 50000);

    _step++;
    if (_step % 1000 == 0)
    {
        _cpTime = (_cpTime + 24 * 60 - 1) % (24 * 60);
    }

    if (_step % 16 == 0)
    {
        for (uint8_t x = 0; x < 72; x++)
        {
            for (uint8_t y = 0; y < 5; y++)
            {
                send.Pixel(x, y,
                    _random.GetNext() % 255, _random.GetNext() % 255, _random.GetNext() % 255);
            }
        }
        send.FrameReady();
    }

    _player1++;
    _player2 += 13;
    send.Value(Types::ETm1637Id::Player1, _player1);
    send.Value(Types::ETm1637Id::Player2, _player2);
    send.Time(Types::ETm1637Id::CentralPanel, (uint16_t) _player1 / 100 / 60, (_player1 / 100) % 60);
    send.Led(Types::ELedId::Player1, _step % 500 < 250);
    send.Led(Types::ELedId::Player2, _step % 1000 < 800);
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

