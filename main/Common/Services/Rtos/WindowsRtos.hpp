#pragma once

#include "Rtos.hpp"
#include <cstdint>

class WindowsRtos : public Rtos
{
public:
	WindowsRtos();
	~WindowsRtos() = default;

    bool CreateTask(TaskFunction_t taskFunction, const char* const name,
        uint32_t stackSize, uint8_t priority, uint8_t core) override;
};
