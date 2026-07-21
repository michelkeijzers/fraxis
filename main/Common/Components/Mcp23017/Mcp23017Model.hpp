#pragma once

#include "../ComponentModel.hpp"
#include <cstdint>

class Mcp23017Model : ComponentModel
{
public:
    /// @param inputPins port A (MSB byte), port B (LSB byte) 
    Mcp23017Model(uint16_t inputPinsMask);

    uint16_t GetInputPinsMask() const;

    bool GetPin(uint8_t pinIndex) const;
    void SetOutputPin(uint8_t pinIndex, bool onOff);
    void SetPinWithoutCheck(uint8_t pinIndex, bool isInput); // WIndows only (TODO: Check?)

    bool IsInputPin(uint8_t pinIndex) const;
    
private: // ONLY FOR WINDOWS to set
    uint8_t _gpioStatesPortA;
    uint8_t _gpioStatesPortB;

    uint8_t _gpioPreviousStatesPortA;
    uint8_t _gpioPreviousStatesPortB;

    /// TODO check against previou states, and set pin transitions, 
    // let i2ctask read pin transitions, send a message to the queue  and reset (?).

    // Readonly.
    uint8_t _gpioDirectionPortA; // Inputs
    uint8_t _gpioDirectionPortB;
};
