#pragma once

#include "../../Core/Components/Mcp23017.hpp"

class WindowsMcp23017 : Mcp23017
{
public:
	WindowsMcp23017();
	~WindowsMcp23017();

	void Initialize() override;
	void SetDirectionBytes(uint8_t iodira, uint8_t iodirb) override;

	uint16_t GetGpioStates() const override;
	void SetGpioStates(uint16_t gpioStates) override;
};
