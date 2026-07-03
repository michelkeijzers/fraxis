#include "PinIo.hpp"
#include "PinIoMappings.hpp"
#include "Mcp23017.hpp"

PinIo::PinIo(Mcp23017& mcp23017) : _mcp23017(mcp23017), _gpioStates(0), _previousGpios(0)
{
}

PinIo::~PinIo()
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
    EJoystickDirection direction = EJoystickDirection::None;
    switch (playerId)
    {
    case EPlayerId::Player1:
        if (BecamePressed(PinIoMappings::EId::Player1Up))
        {
            if (BecamePressed(PinIoMappings::EId::Player1Right))
            {
                direction = EJoystickDirection::UpRight;
            }
            if (BecamePressed(PinIoMappings::EId::Player1Left))
            {
                direction = EJoystickDirection::UpLeft;
            }
            else 
            {
                direction = EJoystickDirection::Up;
            }
        }
        else if (BecamePressed(PinIoMappings::EId::Player1Down))
        {
            if (BecamePressed(PinIoMappings::EId::Player1Right))
            {
                direction = EJoystickDirection::DownRight; 
            }
            if (BecamePressed(PinIoMappings::EId::Player1Left))
            {
                direction = EJoystickDirection::DownLeft;
            }
            else
            {
                direction = EJoystickDirection::Down;
            }
        }
        else if (BecamePressed(PinIoMappings::EId::Player1Right))
        {
            direction = EJoystickDirection::Right;
        }
        else if (BecamePressed(PinIoMappings::EId::Player1Left))
        {
            direction = EJoystickDirection::Left;
        }
        break;

    case EPlayerId::Player2:
        if (BecamePressed(PinIoMappings::EId::Player2Up))
        {
            if (BecamePressed(PinIoMappings::EId::Player2Right))
            {
                direction =  EJoystickDirection::UpRight;
            }
            if (BecamePressed(PinIoMappings::EId::Player2Left))
            {
                direction =  EJoystickDirection::UpLeft;
            }
            else 
            {
                direction = EJoystickDirection::Up;
            }
        }
        else if (BecamePressed(PinIoMappings::EId::Player2Down))
        {
            if (BecamePressed(PinIoMappings::EId::Player2Right))
            {
                direction = EJoystickDirection::DownRight; 
            }
            if (BecamePressed(PinIoMappings::EId::Player2Left))
            {
                direction = EJoystickDirection::DownLeft;
            }
            else 
            {
                direction = EJoystickDirection::Down;
            }
        }
        else if (BecamePressed(PinIoMappings::EId::Player2Right))
        {
            direction = EJoystickDirection::Right;
        }
        else if (BecamePressed(PinIoMappings::EId::Player2Left))
        {
            direction = EJoystickDirection::Left;
        }
        break;

    default:
        break;
    }   
    return direction;
}

bool PinIo::GetJoystickButton(PinIo::EPlayerId playerId) const
{
    switch (playerId)
    {
        case PinIo::EPlayerId::Player1:
            return BecamePressed(PinIoMappings::EId::Player1Button);
            break;
        case PinIo::EPlayerId::Player2:
            return BecamePressed(PinIoMappings::EId::Player2Button);
            break;
        default:
            break;
    }
    return false;
}

bool PinIo::IsSystemButtonPressed() const
{
    return BecamePressed(PinIoMappings::EId::SystemButton);
}

void PinIo::SetPauseLed(bool paused)
{
    if (paused)
        _gpioStates |= (1 << (uint16_t) PinIoMappings::EId::PauseLed);
    else
        _gpioStates &= ~(1 << (uint16_t) PinIoMappings::EId::PauseLed);
}

bool PinIo::IsPauseLedOn() const
{
    return _gpioStates & (1 << (int16_t) PinIoMappings::EId::PauseLed);
}

void PinIo::SetSelectLed(bool on)
{
    if (on)
        _gpioStates |= (1 << (uint16_t) PinIoMappings::EId::SelectLed);
    else
        _gpioStates &= ~(1 << (uint16_t)PinIoMappings::EId::SelectLed);
}

bool PinIo::IsSelectLedOn() const
{
    return _gpioStates & (1 << (uint16_t)PinIoMappings::EId::SelectLed);
}

void PinIo::SetSettingsLed(bool on)
{
    if (on)
        _gpioStates |= (1 << (uint16_t)PinIoMappings::EId::SettingsLed); 
    else
        _gpioStates &= ~(1 << (uint16_t)PinIoMappings::EId::SettingsLed);
}

bool PinIo::IsSettingsLedOn() const
{
    return _gpioStates & (1 << (uint16_t)PinIoMappings::EId::SettingsLed);
}

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
