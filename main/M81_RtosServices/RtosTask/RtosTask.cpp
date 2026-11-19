// @file RtosTask.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "RtosTask.hpp"

namespace M81::RtosTask
{
    RtosTask::RtosTask(
        M90::Assert::IAssert& assert)
    :
        Service(assert)
    {
        // No fuctionality required.
    }
}
