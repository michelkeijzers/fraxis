#pragma once

#include <cstdint>

class RtosQueue;

class RtosTask
{
public:
    // NOLINTNEXTLINE(modernize-use-using)
    typedef void (*TaskFunction_t)(void*);

    RtosTask() = default;

    RtosTask(const RtosTask&) = delete;
    RtosTask& operator=(const RtosTask&) = delete;
    RtosTask(RtosTask&&) = delete;
    RtosTask& operator=(RtosTask&&) = delete;

    virtual ~RtosTask() = default;
    
    virtual void Start() = 0;

    virtual bool DelayTask(
        uint32_t microSeconds) = 0;
    virtual uint32_t GetTaskTickCount() = 0;
};
