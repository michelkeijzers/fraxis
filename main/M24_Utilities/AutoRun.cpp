#include "AutoRun.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M20_Applications/ApplicationsManager.hpp"
#include "../M30_Messages/Types.hpp"
#include "../M80_Services/Random/Random.hpp"

static constexpr std::array<IApplication::ETag, 3> TAGS =
{
    IApplication::ETag::LedStrips,
    IApplication::ETag::Leds,
    IApplication::ETag::Displays
};

AutoRun::AutoRun(
    Context& context, 
    M90::String::IStringUtilities& stringUtilities,
    ApplicationsManager& applicationsManager) 
:   
    Application(EApplicationId::AutoRun, context, stringUtilities, applicationsManager),
    _random(context.GetServices().GetRandom()),
    _step(0),
    _cpTime(0),
    _player1(0),
    _player2(100000)
{
}

void AutoRun::Tick()
{
    if (GetState() != IApplication::EState::Running)
    {
        return;
    }

    GetApplicationsManager().GetQueueWriters();

    Send& send = GetSend();
    send.Tm1637Enable(Types::ETm1637Id::CentralPanel, true);
    send.Tm1637Enable(Types::ETm1637Id::Player1, true);
    send.Tm1637Enable(Types::ETm1637Id::Player2, true);

    //send.Value(Types::ETm1637Id::Player1, 50000);

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
                send.Pixel(
                    x, 
                    y, 
                    static_cast<uint8_t>(_random.GetNext() % 255),
                    static_cast<uint8_t>(_random.GetNext() % 255),
                    static_cast<uint8_t>(_random.GetNext() % 255));
            }
        }
        send.FrameReady();
    }

    _player1++;
    if (_player1 > 9999)
    {
        _player1 = 100;
    }
    _player2 += 13;
    send.Value(Types::ETm1637Id::Player1, _player1);
    send.Value(Types::ETm1637Id::Player2, _player2);
    send.Time(
        Types::ETm1637Id::CentralPanel, 
        static_cast<uint8_t>((_player1 / 100) / 60), 
        static_cast<uint8_t>((_player1 / 100) % 60));
    
    if (_step % 100 == 0)
    {
        send.Led(Types::ELedId::PlayPause, _step % 30 == 0);
    }
    send.Led(Types::ELedId::Select, _step % 300 < 50);
    send.Led(Types::ELedId::Player1, _step % 500 < 250);
    send.Led(Types::ELedId::Player2, _step % 1000 < 800);
    send.Led(Types::ELedId::Setup, _step % 1000 < 10);


}

void AutoRun::OnJoystickDirectionChanged(
Types::EJoystickId,
    Types::EJoystickDirection)
{
    // No actions required
}

void AutoRun::OnJoystickButtonChanged(
    Types::EJoystickId,
    bool)
{
    // No actions required
}

void AutoRun::OnSystemButtonChanged(
    bool)
{
    // No actions required
}
