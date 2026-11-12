// @file Task.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

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
