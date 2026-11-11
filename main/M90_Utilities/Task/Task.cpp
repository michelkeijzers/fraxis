#include "Task.hpp"
#include "../../M81_RtosServices/RtosTask/RtosTask.hpp"

namespace M90::Task
{
    void Task::SetRtosTask(
        M81::RtosTask::RtosTask& rtosTask)
    {
        _rtosTask = &rtosTask;
    }

    M81::RtosTask::RtosTask& Task::GetRtosTask()
    {
        return *_rtosTask;
    }
}
