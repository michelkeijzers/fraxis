#include "PinIo.hpp"
#include "PinIoMappings.hpp"
#include "Mcp23017.hpp"

#include "../SharedUtils/Debug.hpp"

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

    uint8_t ioDirectionPortA = CalculateDirectionByte(0, inputIds);
    uint8_t ioDirectionPortB = CalculateDirectionByte(1, inputIds);

    _mcp23017.SetDirectionBytes(ioDirectionPortA, ioDirectionPortB);
}

void PinIo::Update()
{
    _previousGpios = _gpioStates;
    _gpioStates = _mcp23017.UpdateInputsAndOutputs(_gpioStates);

    uint16_t changed = _gpioStates ^ _previousGpios;
    for (uint8_t bit = 0; bit < 16; bit++)
    {
        uint16_t mask = 1 << bit;

        if (changed & mask)
        {
            bool nowPressed = (_gpioStates & mask) != 0;

            InputEvent inputEvent;
            inputEvent.idBit = static_cast<PinIoMappings::EIdBit>(bit);
            inputEvent.type = nowPressed ? InputEvent::EType::Pressed
                : InputEvent::EType::Released;
            _inputEvents.push_back(inputEvent);
        }
    }
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
void PinIo::SetPlayer2Led(bool on) { SetLed(PinIoMappings::EIdBit::Player2Led, on); }

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
            dir |= (1 << PinIoMappings::GetPin(inputId));   // 1 = input
        }
    }

    return dir;
}


std::vector<PinIo::InputEvent>& PinIo::GetInputEvents()
{
    return _inputEvents;
}