
#pragma once

#include "../../Core/Components/LedStrips.hpp"
#include <cstdint>

class WindowsLedStrips : public LedStrips
{
public:
	WindowsLedStrips();

	void Initialize() override;
	void Update() override;

private:
};


