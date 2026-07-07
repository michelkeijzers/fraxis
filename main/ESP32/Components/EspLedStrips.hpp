
#pragma once

#include "../../Core/Components/LedStrips.hpp"
#include <cstdint>

class EspLedStrips : public LedStrips
{
public:
	EspLedStrips();

	void Initialize() override;
	void Update() override;

private:
};


