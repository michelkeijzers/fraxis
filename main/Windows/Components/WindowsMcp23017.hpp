#pragma once

#include "../../Core/Components/Mcp23017.hpp"
#include "../../Core/Components/PinIoMappings.hpp"

class WindowsMcp23017 : public Mcp23017
{
public:
	WindowsMcp23017();
	~WindowsMcp23017();

	void Initialize() override;
	void SetDirectionBytes(uint8_t iodira, uint8_t iodirb) override;

	uint16_t GetGpioStates() const override;
	void SetGpioStates(uint16_t gpioStates) override;

	// Windows only.
	void SimulateSetGpioPin(PinIoMappings::EId id, uint8_t value);
	void SimulateResetGpioPins();
private:
	uint16_t _gpioStates;
};
