#pragma once

#include "Rtos.hpp"
#include <cstdint>

class RtosTask;

class WindowsRtos : public Rtos
{
public:
	WindowsRtos();
	~WindowsRtos() = default;

    RtosTask* CreateTask(TaskFunction_t taskFunction, const char* const name,
        uint32_t stackSize, uint8_t priority, uint8_t core, void* param) override;


    RtosQueue* CreateQueue(uint32_t queueLength, uint32_t itemSize) override;
};
