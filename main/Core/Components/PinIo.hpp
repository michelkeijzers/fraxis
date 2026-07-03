#pragma once

#include "IComponent.hpp"
#include <cstdint>
#include <vector>

class Mcp23017;

class PinIo : public IComponent
{
public:
	enum class EPlayerId
	{
		Player1 = 0,
		Player2 = 1
	};

	enum class EJoystickDirection
	{
        None,
	    Up,
        UpRight,
        Right,
        DownRight,
        Down,
        DownLeft,
        Left,
        UpLeft
	};

	PinIo(Mcp23017& mcp23017);
	~PinIo();

    void Initialize() override;
    
    void Update() override;

    bool BecamePressed(uint8_t port, uint8_t pin) const;
    EJoystickDirection GetJoystickDirection(EPlayerId playerId) const;

    bool GetJoystickButton(EPlayerId playerId) const;
    bool IsSystemButtonPressed() const;

    void SetPauseLed(bool paused);
    bool IsPauseLedOn() const;
    void SetSelectLed(bool on);
    bool IsSelectLedOn() const;
    void SetSettingsLed(bool on);
    bool IsSettingsLedOn() const;

    uint8_t CalculateDirectionByte(uint8_t port, const std::vector<uint8_t>& inputPins);

	 void SetGpios(uint16_t gpioStates); // ONLY USE FOR WINDOWS

private:
    Mcp23017& _mcp23017;

    uint16_t _gpioStates;
    uint16_t _previousGpios;

private:
    void PushBack(std::vector<uint8_t>& portAInputs, std::vector<uint8_t>& portBInputs, uint8_t port, uint8_t pin);
};
