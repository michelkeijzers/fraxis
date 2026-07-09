#pragma once

#include "RtosTask.hpp"
#include <cstdint>

class WindowsRtosTask : public RtosTask
{
public:
	WindowsRtosTask();
	~WindowsRtosTask() = default;

    bool DelayTask(uint32_t ms) override;
    uint32_t GetTaskTickCount() override;

    bool CreateQueue(uint32_t queueLength, uint32_t itemSize) override;
};
