#pragma once

#include <cstdint>
#include "../../Core/Services/Timer.hpp"

class WindowsTimer : public ITimer
{
public:
	WindowsTimer();
	~WindowsTimer();

	uint32_t GetTimeInMs();
};
