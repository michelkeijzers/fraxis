// @file Task.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../../M81_RtosServices/RtosTask/IRtosTask.hpp"

namespace M90::Task
{
    class Task
    {
    public:
        Task() = default;

        Task(
            const Task&) = delete;

        Task& operator=(
            const Task&) = delete;

        Task(
            Task&&) = delete;

        Task& operator=(
            Task&&) = delete;

        virtual ~Task() = default;

        void SetRtosTask(
            M81::RtosTask::IRtosTask& rtosTask);

        M81::RtosTask::IRtosTask& GetRtosTask();

        virtual void Initialize() = 0;

        virtual void Run() = 0;

    private:
        M81::RtosTask::IRtosTask* _rtosTask;
    };
}
