#include "PinIo.hpp"
#include "PinIoMappings.hpp"
#include "Mcp23017.hpp"

PinIo::PinIo(Mcp23017& mcp23017) : _mcp23017(mcp23017), _gpioStates(0), _previousGpios(0)
{
}

void PinIo::Initialize()
{
    std::vector<PinIoMappings::EId> inputIds =
    {
        PinIoMappings::EId::Player1Up,
        PinIoMappings::EId::Player1Down,
        PinIoMappings::EId::Player1Left,
        PinIoMappings::EId::Player1Right,
        PinIoMappings::EId::Player1Button,

        PinIoMappings::EId::Player2Up,
        PinIoMappings::EId::Player2Down,
        PinIoMappings::EId::Player2Left,
        PinIoMappings::EId::Player2Right,
        PinIoMappings::EId::Player2Button,

        PinIoMappings::EId::SystemButton
    };

    uint8_t iodira = CalculateDirectionByte(0, inputIds);
    uint8_t iodirb = CalculateDirectionByte(1, inputIds);

    _mcp23017.SetDirectionBytes(iodira, iodirb);
}

void PinIo::Update()
{
    _previousGpios = _gpioStates;
    _gpioStates = _mcp23017.GetGpioStates();
	 _mcp23017.SetGpioStates(_gpioStates);
}

bool PinIo::BecamePressed(PinIoMappings::EId id) const
{
    int pinValue = 1 << (uint16_t) id;
    uint16_t current  = _gpioStates    & pinValue;
    uint16_t previous = _previousGpios & pinValue;
    return current && !previous;
}

PinIo::EJoystickDirection PinIo::GetJoystickDirection(EPlayerId playerId) const
{
    const auto up = (playerId == EPlayerId::Player1) ? PinIoMappings::EId::Player1Up : PinIoMappings::EId::Player2Up;
    const auto down = (playerId == EPlayerId::Player1) ? PinIoMappings::EId::Player1Down : PinIoMappings::EId::Player2Down;
    const auto left = (playerId == EPlayerId::Player1) ? PinIoMappings::EId::Player1Left : PinIoMappings::EId::Player2Left;
    const auto right = (playerId == EPlayerId::Player1) ? PinIoMappings::EId::Player1Right : PinIoMappings::EId::Player2Right;

    const bool upPressed = BecamePressed(up);
    const bool downPressed = BecamePressed(down);
    const bool leftPressed = BecamePressed(left);
    const bool rightPressed = BecamePressed(right);

    if (upPressed && rightPressed)  return EJoystickDirection::UpRight;
    if (upPressed && leftPressed)   return EJoystickDirection::UpLeft;
    if (downPressed && rightPressed) return EJoystickDirection::DownRight;
    if (downPressed && leftPressed)  return EJoystickDirection::DownLeft;

    if (upPressed)    return EJoystickDirection::Up;
    if (downPressed)  return EJoystickDirection::Down;
    if (rightPressed) return EJoystickDirection::Right;
    if (leftPressed)  return EJoystickDirection::Left;

    return EJoystickDirection::None;
}

bool PinIo::GetJoystickButton(PinIo::EPlayerId playerId) const
{
    switch (playerId)
    {
        case PinIo::EPlayerId::Player1: return BecamePressed(PinIoMappings::EId::Player1Button); break;
        case PinIo::EPlayerId::Player2: return BecamePressed(PinIoMappings::EId::Player2Button); break;
        default: break;
    }
    return false;
}

bool PinIo::IsSystemButtonPressed() const
{
    return BecamePressed(PinIoMappings::EId::SystemButton);
}

constexpr uint16_t PinIo::Mask(PinIoMappings::EId id)
{
    return 1u << static_cast<uint16_t>(id);
}

void PinIo::SetLed(PinIoMappings::EId id, bool on)
{
    uint16_t mask = Mask(id);
    _gpioStates = (_gpioStates & ~mask) | (on ? mask : 0u);
}

bool PinIo::IsLedOn(PinIoMappings::EId id) const
{
    return _gpioStates & Mask(id);
}

void PinIo::SetPauseLed(bool on) { SetLed(PinIoMappings::EId::PauseLed, on); }
void PinIo::SetSelectLed(bool on) { SetLed(PinIoMappings::EId::SelectLed, on); }
void PinIo::SetSettingsLed(bool on) { SetLed(PinIoMappings::EId::SettingsLed, on); }

bool PinIo::IsPauseLedOn() const { return IsLedOn(PinIoMappings::EId::PauseLed); }
bool PinIo::IsSelectLedOn() const { return IsLedOn(PinIoMappings::EId::SelectLed); }
bool PinIo::IsSettingsLedOn() const { return IsLedOn(PinIoMappings::EId::SettingsLed); }

uint8_t PinIo::CalculateDirectionByte(uint8_t port, const std::vector<PinIoMappings::EId>& inputIds)
{
    uint8_t dir = 0;

    for (PinIoMappings::EId inputId : inputIds)
    {
        if (port == PinIoMappings::GetPort(inputId))
        {
            dir |= (1 << PinIoMappings::GetPin(inputId));   // 1 = input
        }
    }

    return dir;
}

/// <summary>
/// Only8 use for Windows testing
/// </summary>
/// <param name="gpioStates"></param>
void PinIo::SetGpios(uint16_t gpioStates)
{
	_gpioStates = gpioStates;
}
