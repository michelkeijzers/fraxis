// @file Task.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Task.hpp"

namespace M90::Task
{
    Task::Task(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log)
    :
        _assert(assert),
        _log(log)
    {
        _rtosTask = nullptr;
    }

    void Task::SetRtosTask(
        M81::RtosTask::IRtosTask& rtosTask)
    {
        _rtosTask = &rtosTask;
    }

    M81::RtosTask::IRtosTask& Task::GetRtosTask()
    {
        return *_rtosTask;
    }

    M90::Assert::IAssert& Task::GetAssert() const
    {
        return _assert;
    }

    M90::Log::ILog& Task::GetLog() const
    {
        return _log;
    }
}
