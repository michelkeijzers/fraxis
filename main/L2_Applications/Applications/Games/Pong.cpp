#include "Pong.hpp"
#include "../../../L1_Composition/Context/Context.hpp"
#include "../../../L2_Applications/ApplicationsManager.hpp"
#include "../../../L3_Messages/Types.hpp"
#include "../../../L8_Services/Random/Random.hpp"
#include "../../../L9_Utilities/Time/TimeUtilities.hpp" 

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
    Game(context, applicationsManager),
    _random(context.GetServices().GetRandom()),
    _step(0),
    _cpTime(0),
    _player1(0),
    _player2(100000)
{
}

std::string_view Pong::GetName() const
{
    return "Pong";
}

IApplication::EType Pong::GetType() const
{
    return IApplication::EType::Game;
}

std::span<const IApplication::ETag> Pong::GetTags() const
{
    return TAGS;
}

void Pong::Run()
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
}

void Pong::OnJoystickDirectionChanged(
    Types::EJoystickId id, 
    Types::EJoystickDirection direction)
{
    // TODO
}

void Pong::OnJoystickButtonChanged(
    Types::EJoystickId id, 
    bool state)
{
    // TODO
}

void Pong::OnSystemButtonChanged(
    bool state)
{
    // TODO
}

