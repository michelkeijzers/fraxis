#pragma once

#include "../../Core/Services/IRtos.hpp"

class WindowsRtos : public IRtos
{
public:
	WindowsRtos();
	~WindowsRtos() = default;

    bool CreateTask(TaskFunction_t taskFunction, const char* const name,
        uint32_t stackSize, uint8_t priority, uint8_t core) override;
    bool DelayTask(uint32_t ms) override;
    uint32_t GetTaskTickCount() override;

    bool CreateQueue(uint32_t queueLength, uint32_t itemSize) override;
};
