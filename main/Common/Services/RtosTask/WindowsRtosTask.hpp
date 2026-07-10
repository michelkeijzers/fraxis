#pragma once

#include "RtosTask.hpp"
#include <cstdint>
#include <thread>

class WindowsRtosTask : public RtosTask
{
public:
    WindowsRtosTask(TaskFunction_t func, void* param);
    ~WindowsRtosTask();

    void Start() override;

    bool DelayTask(uint32_t ms) override;
    uint32_t GetTaskTickCount() override;

    bool CreateQueue(uint32_t queueLength, uint32_t itemSize) override;

private:
    TaskFunction_t _func;
    void* _param;
    std::thread _thread;
    bool _started;
};
