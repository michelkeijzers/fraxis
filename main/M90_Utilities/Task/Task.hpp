#pragma once

#include "../../M81_RtosServices/RtosTask/RtosTask.hpp"

class Task
{
public:
    Task();

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    Task(Task&&) = delete;
    Task& operator=(Task&&) = delete;  

    virtual ~Task();

    void SetRtosTask(
        RtosTask& rtosTask);
    RtosTask& GetRtosTask();
    virtual void Initialize() = 0;
    virtual void Run() = 0;

private:
    RtosTask* _rtosTask;
};
