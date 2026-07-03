#include "PinIo.hpp"
#include "PinIoMappings.hpp"
#include "Mcp23017.hpp"

PinIo::PinIo(Mcp23017& mcp23017) : _mcp23017(mcp23017), _gpioStates(0), _previousGpios(0)
{
}

void PinIo::Initialize()
{
    std::vector<PinIoMappings::EIdBit> inputIds =
    {
        PinIoMappings::EIdBit::Player1Up,
        PinIoMappings::EIdBit::Player1Down,
        PinIoMappings::EIdBit::Player1Left,
        PinIoMappings::EIdBit::Player1Right,
        PinIoMappings::EIdBit::Player1Button,

        PinIoMappings::EIdBit::Player2Up,
        PinIoMappings::EIdBit::Player2Down,
        PinIoMappings::EIdBit::Player2Left,
        PinIoMappings::EIdBit::Player2Right,
        PinIoMappings::EIdBit::Player2Button,

        PinIoMappings::EIdBit::SystemButton
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

bool PinIo::BecamePressed(PinIoMappings::EIdBit idBit) const
{
    uint16_t current = _gpioStates & (1 << (uint8_t) idBit);
    uint16_t previous = _previousGpios & (1 << (uint8_t)idBit);
    return current && !previous;
}

PinIo::EJoystickDirection PinIo::GetJoystickDirection(EPlayerId playerId) const
{
    const auto up = (playerId == EPlayerId::Player1) 
        ? PinIoMappings::EIdBit::Player1Up 
        : PinIoMappings::EIdBit::Player2Up;
    const auto down = (playerId == EPlayerId::Player1) 
        ? PinIoMappings::EIdBit::Player1Down 
        : PinIoMappings::EIdBit::Player2Down;
    const auto left = (playerId == EPlayerId::Player1) 
        ? PinIoMappings::EIdBit::Player1Left 
        : PinIoMappings::EIdBit::Player2Left;
    const auto right = (playerId == EPlayerId::Player1) 
        ? PinIoMappings::EIdBit::Player1Right 
        : PinIoMappings::EIdBit::Player2Right;

    const bool upPressed = BecamePressed(up);
    const bool downPressed = BecamePressed(down);
    const bool leftPressed = BecamePressed(left);
    const bool rightPressed = BecamePressed(right);

    if (upPressed && rightPressed)   return EJoystickDirection::UpRight;
    if (upPressed && leftPressed)    return EJoystickDirection::UpLeft;
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
        case PinIo::EPlayerId::Player1: return BecamePressed(PinIoMappings::EIdBit::Player1Button); break;
        case PinIo::EPlayerId::Player2: return BecamePressed(PinIoMappings::EIdBit::Player2Button); break;
        default: break;
    }
    return false;
}

bool PinIo::IsSystemButtonPressed() const
{
    return BecamePressed(PinIoMappings::EIdBit::SystemButton);
}

void PinIo::SetLed(PinIoMappings::EIdBit idBit, bool on)
{
    uint16_t idValue = 1 << (uint8_t)idBit;
    _gpioStates = (_gpioStates & ~idValue) | (on ? idValue : 0u);
}

bool PinIo::IsLedOn(PinIoMappings::EIdBit idBit) const
{
    uint16_t idValue = 1 << (uint8_t)idBit;
    return _gpioStates & idValue;
}

void PinIo::SetPauseLed(bool on) { SetLed(PinIoMappings::EIdBit::PauseLed, on); }
void PinIo::SetSelectLed(bool on) { SetLed(PinIoMappings::EIdBit::SelectLed, on); }
void PinIo::SetSetupLed(bool on) { SetLed(PinIoMappings::EIdBit::SetupLed, on); }
void PinIo::SetPlayer1Led(bool on) { SetLed(PinIoMappings::EIdBit::Player1Led, on); }
void PinIo::SetPlayer2Led(bool on) { SetLed(PinIoMappings::EIdBit::Player1Led, on); }

bool PinIo::IsPauseLedOn() const { return IsLedOn(PinIoMappings::EIdBit::PauseLed); }
bool PinIo::IsSelectLedOn() const { return IsLedOn(PinIoMappings::EIdBit::SelectLed); }
bool PinIo::IsSetupLedOn() const { return IsLedOn(PinIoMappings::EIdBit::SetupLed); }
bool PinIo::IsPlayer1LedOn() const { return IsLedOn(PinIoMappings::EIdBit::Player1Led); }
bool PinIo::IsPlayer2LedOn() const { return IsLedOn(PinIoMappings::EIdBit::Player2Led); }


uint8_t PinIo::CalculateDirectionByte(uint8_t port, const std::vector<PinIoMappings::EIdBit>& inputIds)
{
    uint8_t dir = 0;

    for (PinIoMappings::EIdBit inputId : inputIds)
    {
        if (port == PinIoMappings::GetPort(inputId))
        {
            dir |= PinIoMappings::GetPin(inputId);   // 1 = input
        }
    }

    return dir;
}

