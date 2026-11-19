// @file RtosQueue.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "RtosQueue.hpp"

namespace M81::RtosQueue
{
    RtosQueue::RtosQueue(
        M90::Assert::IAssert& assert)
    :
        Service(assert)
    {
        // No fuctionality required.
    }
}
