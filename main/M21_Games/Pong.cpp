#include "Pong.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M20_Applications/ApplicationsManager.hpp"
#include "../M30_Messages/Types.hpp"
#include "../M80_Services/Random/Random.hpp"
#include "../M90_Utilities/Time/TimeUtilities.hpp" 

static constexpr std::array<IApplication::ETag, 3> TAGS =
{
    IApplication::ETag::Arcade,
    IApplication::ETag::Vertical,
    IApplication::ETag::TwoPlayers
};

Pong::Pong(
    Context& context, 
    ApplicationsManager& applicationsManager) 
:   
    Game(EApplicationId::Pong, context, applicationsManager),
    _random(context.GetServices().GetRandom()),
    _step(0),
    _cpTime(0),
    _player1(0),
    _player2(100000)
{
}

void Pong::Tick()
{
    if (GetState() != IApplication::EState::Running)
    {
        return;
    }

    GetApplicationsManager().GetQueueWriters();

    Send& send = GetSend();
    using enum Types::ETm1637Id;
    send.Tm1637Enable(CentralPanel, true);
    send.Tm1637Enable(Player1, true);
    send.Tm1637Enable(Player2, true);

    send.Value(Player1, 50000);
}

void Pong::OnJoystickDirectionChanged(
    Types::EJoystickId,
    Types::EJoystickDirection)
{
    // NOSONAR TODO
}

void Pong::OnJoystickButtonChanged(
    Types::EJoystickId /* NOSONAR TODO id */,
    bool /* NOSONAR TODO state */ )
{
    // NOSONAR TODO state
}

void Pong::OnSystemButtonChanged(
    bool /* NOSONAR TODO state */)
{
    // NOSONAR TODO state
}

