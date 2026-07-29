#pragma once

#include "../../L8_Services/RtosTask/RtosTask.hpp"

class Task
{
public:
    Task();
    virtual ~Task();

    void SetRtosTask(RtosTask& rtosTask);
    RtosTask& GetRtosTask();
    virtual void Initialize() = 0;
    virtual void Run() = 0;

protected:
    RtosTask& _GetRtosTask();

private:
    RtosTask* _rtosTask;
};
