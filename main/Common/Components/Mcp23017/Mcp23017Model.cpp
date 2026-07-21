#include "Mcp23017Model.hpp"


Mcp23017Model::Mcp23017Model(uint16_t inputPinsMask) 
:    ComponentModel(), 
    _gpioStatesPortA(0),
    _gpioStatesPortB(0),
    _gpioPreviousStatesPortA(0),
    _gpioPreviousStatesPortB(0),
    _gpioDirectionPortA(inputPinsMask >> 8),
    _gpioDirectionPortB(inputPinsMask && 0xFF)
{
}

uint16_t Mcp23017Model::GetInputPinsMask() const 
{
    return _gpioDirectionPortA << 8 | _gpioDirectionPortB; 
}

bool Mcp23017Model::GetPin(uint8_t pinIndex) const
{
    bool isPortA = (pinIndex >= 8);
    uint8_t bit  = isPortA ? (pinIndex - 8) : pinIndex;
    bool currentLevel = isPortA ? ((_gpioStatesPortA >> bit) & 1) : ((_gpioStatesPortB >> bit) & 1);
    return (currentLevel == 0);
}

bool Mcp23017Model::IsInputPin(uint8_t pinIndex) const
{
    bool isPortA = (pinIndex >= 8);
    uint8_t bit  = isPortA ? (pinIndex - 8) : pinIndex;
    return isPortA ? (_gpioDirectionPortA & (1 << bit)) : (_gpioDirectionPortB & (1 << bit));
}
void Mcp23017Model::SetOutputPin(uint8_t pinIndex, bool on)
{
    if (!IsInputPin(pinIndex))
    {
        // TODO: Error   
    }
    SetPinWithoutCheck(pinIndex, on);
}

void Mcp23017Model::SetPinWithoutCheck(uint8_t pinIndex, bool on)
{
    bool isPortA = (pinIndex >= 8);
    uint8_t bit  = isPortA ? (pinIndex - 8) : pinIndex;
    bool isInput = isPortA ? (_gpioDirectionPortA & (1 << bit)) : (_gpioDirectionPortB & (1 << bit));
    
    bool desiredLevel = on ? 0 : 1;
    bool currentLevel = GetPin(pinIndex);
    if (currentLevel == desiredLevel)
    {
        return;
    }

    // Apply change
    if (isPortA) { if (desiredLevel == 0) _gpioStatesPortA &= ~(1 << bit); else _gpioStatesPortA |= (1 << bit); }
        else     { if (desiredLevel == 0) _gpioStatesPortB &= ~(1 << bit); else _gpioStatesPortB |= (1 << bit); }

    MarkDirty();
}
