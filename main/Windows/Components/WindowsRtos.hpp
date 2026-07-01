#pragma once

#include "../../Core/Services/rtos.hpp"

class WindowsRtos : public IRtos
{
public:
	WindowsRtos();
	~WindowsRtos();

	void vTaskDelay(int ms);
};
