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
    std::vector<uint8_t> portAInputs;
    std::vector<uint8_t> portBInputs;

    PushBack(portAInputs, portBInputs, PinIoMappings::PLAYER_1_UP_PORT,     PinIoMappings::PLAYER_1_UP_PIN   );
    PushBack(portAInputs, portBInputs, PinIoMappings::PLAYER_1_DOWN_PORT,   PinIoMappings::PLAYER_1_DOWN_PIN );
    PushBack(portAInputs, portBInputs, PinIoMappings::PLAYER_1_LEFT_PORT,   PinIoMappings::PLAYER_1_LEFT_PIN );
    PushBack(portAInputs, portBInputs, PinIoMappings::PLAYER_1_RIGHT_PORT,  PinIoMappings::PLAYER_1_RIGHT_PIN);
    PushBack(portAInputs, portBInputs, PinIoMappings::PLAYER_1_BUTTON_PORT, PinIoMappings::PLAYER_1_BUTTON_PIN);

    PushBack(portAInputs, portBInputs, PinIoMappings::PLAYER_2_UP_PORT,     PinIoMappings::PLAYER_2_UP_PIN   );
    PushBack(portAInputs, portBInputs, PinIoMappings::PLAYER_2_DOWN_PORT,   PinIoMappings::PLAYER_2_DOWN_PIN );
    PushBack(portAInputs, portBInputs, PinIoMappings::PLAYER_2_LEFT_PORT,   PinIoMappings::PLAYER_2_LEFT_PIN );
    PushBack(portAInputs, portBInputs, PinIoMappings::PLAYER_2_RIGHT_PORT,  PinIoMappings::PLAYER_2_RIGHT_PIN);
    PushBack(portAInputs, portBInputs, PinIoMappings::PLAYER_2_BUTTON_PORT, PinIoMappings::PLAYER_2_BUTTON_PIN);

    PushBack(portAInputs, portBInputs, PinIoMappings::SYSTEM_BUTTON_PORT, PinIoMappings::SYSTEM_BUTTON_PIN);

    uint8_t iodira = CalculateDirectionByte(1, portAInputs);
    uint8_t iodirb = CalculateDirectionByte(0, portBInputs);

    _mcp23017.SetDirectionBytes(iodira, iodirb);
}

void PinIo::PushBack(std::vector<uint8_t>& portAInputs, std::vector<uint8_t>& portBInputs, uint8_t port, uint8_t pin)
{
    if (port == 0) 
    {
        portAInputs.push_back(pin);
    }
    else
    {
        portBInputs.push_back(pin);
    }   
}

void PinIo::Update()
{
    _previousGpios = _gpioStates;
    _gpioStates = _mcp23017.GetGpioStates();
	 _mcp23017.SetGpioStates(_gpioStates);
}

bool PinIo::BecamePressed(uint8_t port, uint8_t pin) const
{
    int pinValue = 1 << (port * 8 + pin);
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
        if (BecamePressed(PinIoMappings::PLAYER_1_UP_PORT, PinIoMappings::PLAYER_1_UP_PIN))
        {
            if (BecamePressed(PinIoMappings::PLAYER_1_RIGHT_PORT, PinIoMappings::PLAYER_1_RIGHT_PIN)) 
            {
                direction = EJoystickDirection::UpRight;
            }
            if (BecamePressed(PinIoMappings::PLAYER_1_LEFT_PORT , PinIoMappings::PLAYER_1_LEFT_PIN))  
            {
                direction = EJoystickDirection::UpLeft;
            }
            else 
            {
                direction = EJoystickDirection::Up;
            }
        }
        else if (BecamePressed(PinIoMappings::PLAYER_1_DOWN_PORT, PinIoMappings::PLAYER_1_DOWN_PIN))
        {
            if (BecamePressed(PinIoMappings::PLAYER_1_RIGHT_PORT, PinIoMappings::PLAYER_1_RIGHT_PIN)) 
            {
                direction = EJoystickDirection::DownRight; 
            }
            if (BecamePressed(PinIoMappings::PLAYER_1_LEFT_PORT , PinIoMappings::PLAYER_1_LEFT_PIN))  
            {
                direction = EJoystickDirection::DownLeft;
            }
            else
            {
                direction = EJoystickDirection::Down;
            }
        }
        else if (BecamePressed(PinIoMappings::PLAYER_1_RIGHT_PORT, PinIoMappings::PLAYER_1_RIGHT_PIN)) 
        {
            direction = EJoystickDirection::Right;
        }
        else if (BecamePressed(PinIoMappings::PLAYER_1_LEFT_PORT , PinIoMappings::PLAYER_1_LEFT_PIN))  
        {
            direction = EJoystickDirection::Left;
        }
        break;

    case EPlayerId::Player2:
        if (BecamePressed(PinIoMappings::PLAYER_2_UP_PORT, PinIoMappings::PLAYER_2_UP_PIN))
        {
            if (BecamePressed(PinIoMappings::PLAYER_2_RIGHT_PORT, PinIoMappings::PLAYER_2_RIGHT_PIN)) 
            {
                direction =  EJoystickDirection::UpRight;
            }
            if (BecamePressed(PinIoMappings::PLAYER_2_LEFT_PORT , PinIoMappings::PLAYER_2_LEFT_PIN))  
            {
                direction =  EJoystickDirection::UpLeft;
            }
            else 
            {
                direction = EJoystickDirection::Up;
            }
        }
        else if (BecamePressed(PinIoMappings::PLAYER_2_DOWN_PORT, PinIoMappings::PLAYER_2_DOWN_PIN))
        {
            if (BecamePressed(PinIoMappings::PLAYER_2_RIGHT_PORT, PinIoMappings::PLAYER_2_RIGHT_PIN)) 
            {
                direction = EJoystickDirection::DownRight; 
            }
            if (BecamePressed(PinIoMappings::PLAYER_2_LEFT_PORT , PinIoMappings::PLAYER_2_LEFT_PIN)) 
            {
                direction = EJoystickDirection::DownLeft;
            }
            else 
            {
                direction = EJoystickDirection::Down;
            }
        }
        else if (BecamePressed(PinIoMappings::PLAYER_2_RIGHT_PORT, PinIoMappings::PLAYER_2_RIGHT_PIN)) 
        {
            direction = EJoystickDirection::Right;
        }
        else if (BecamePressed(PinIoMappings::PLAYER_2_LEFT_PORT , PinIoMappings::PLAYER_2_LEFT_PIN)) 
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
            return BecamePressed(PinIoMappings::PLAYER_1_BUTTON_PORT, PinIoMappings::PLAYER_1_BUTTON_PIN);
            break;
        case PinIo::EPlayerId::Player2:
            return BecamePressed(PinIoMappings::PLAYER_2_BUTTON_PORT, PinIoMappings::PLAYER_2_BUTTON_PIN);
            break;
        default:
            break;
    }
    return false;
}

bool PinIo::IsSystemButtonPressed() const
{
    return BecamePressed(PinIoMappings::SYSTEM_BUTTON_PORT, PinIoMappings::SYSTEM_BUTTON_PIN);
}

void PinIo::SetPauseLed(bool paused)
{
    if (paused)
        _gpioStates |= (1 << PinIoMappings::PAUSE_LED_PIN);
    else
        _gpioStates &= ~(1 << PinIoMappings::PAUSE_LED_PIN);
}

bool PinIo::IsPauseLedOn() const
{
    return _gpioStates & (1 << PinIoMappings::PAUSE_LED_PIN);
}

void PinIo::SetSelectLed(bool on)
{
    if (on)
        _gpioStates |= (1 << PinIoMappings::SELECT_LED_PIN);
    else
        _gpioStates &= ~(1 << PinIoMappings::SELECT_LED_PIN);
}

bool PinIo::IsSelectLedOn() const
{
    return _gpioStates & (1 << PinIoMappings::SELECT_LED_PIN);
}

void PinIo::SetSettingsLed(bool on)
{
    if (on)
        _gpioStates |= (1 << PinIoMappings::SETTINGS_LED_PIN);
    else
        _gpioStates &= ~(1 << PinIoMappings::SETTINGS_LED_PIN);
}

bool PinIo::IsSettingsLedOn() const
{
    return _gpioStates & (1 << PinIoMappings::SETTINGS_LED_PIN);
}

uint8_t PinIo::CalculateDirectionByte(uint8_t port, const std::vector<uint8_t>& inputPins)
{
    uint8_t dir = 0;

    for (uint8_t pin : inputPins)
    {
        if (pin < 8)
        {
            dir |= (1 << pin);   // 1 = input
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
