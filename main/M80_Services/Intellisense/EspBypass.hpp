// @file EspBypass.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#ifdef __INTELLISENSE__

#include "freertos/task.h"

namespace M80::Intellisense
{
    /// <summary>
    /// Intellisense bypass functions/macros for the following ESP specific functions:
    /// - xTaskCreatePinnedToCore
    /// </summary>

    // -> xTaskCreatePinnedToCore
#define TASK_CREATE(taskFunction, name, stackSize, parameter, priority, taskHandle, core) 0
}
#else  // !__INTELLISENSE__

namespace M80::Intellisense
{
#define TASK_CREATE xTaskCreatePinnedToCore
}

#endif
