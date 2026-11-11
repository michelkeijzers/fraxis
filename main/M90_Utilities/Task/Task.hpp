#pragma once

#include "../../M81_RtosServices/RtosTask/RtosTask.hpp"

namespace M90::Task
{
    class Task
    {
    public:
        Task() = default;

        Task(const Task&) = delete;
        Task& operator=(const Task&) = delete;
        Task(Task&&) = delete;
        Task& operator=(Task&&) = delete;

        virtual ~Task() = default;

        void SetRtosTask(
            M81::RtosTask::RtosTask& rtosTask);
        M81::RtosTask::RtosTask& GetRtosTask();
        virtual void Initialize() = 0;
        virtual void Run() = 0;

    private:
        M81::RtosTask::RtosTask* _rtosTask;
    };
}
