#pragma once

#include <cstdint>
#include <vector>
#include <array>
#include "IComponent.hpp"
#include "PinIoMappings.hpp"

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

    void Initialize() override;
    
    void Update() override;
    void Update(uint32_t timeInMs);

    bool BecamePressed(PinIoMappings::EIdBit id) const;
    EJoystickDirection GetJoystickDirection(EPlayerId playerId) const;

    bool GetJoystickButton(EPlayerId playerId) const;
    bool IsSystemButtonPressed() const;

    static constexpr uint16_t Mask(PinIoMappings::EIdBit id);
    void SetLed(PinIoMappings::EIdBit id, bool on);
    bool IsLedOn(PinIoMappings::EIdBit id) const;

    void SetPauseLed(bool paused);
    bool IsPauseLedOn() const;
    void SetSelectLed(bool on);
    bool IsSelectLedOn() const;
    void SetSetupLed(bool on);
    bool IsSetupLedOn() const;
    void SetPlayer1Led(bool on);
    bool IsPlayer1LedOn() const;
    void SetPlayer2Led(bool on);
    bool IsPlayer2LedOn() const;

    uint8_t CalculateDirectionByte(uint8_t port, const std::vector<PinIoMappings::EIdBit>& inputPins);

    uint16_t GetGpioStates() { return _gpioStates; } // ONLY FOR WINDOWS; DIRTY SOLUTION TODO: FIX

private:
    Mcp23017& _mcp23017;

    uint16_t _gpioStates;
    uint16_t _previousGpios;
};
