#pragma once

#ifdef __INTELLISENSE__

#include "freertos/task.h"

/// <summary>
/// Intellisense bypass functions/macros for the following ESP specific functions:
/// - xTaskCreatePinnedToCore
/// </summary>

// -> xTaskCreatePinnedToCore
#define TASK_CREATE(taskFunction, name, stackSize, parameter, priority, taskHandle, core) 0

#else  // !__INTELLISENSE__

#define TASK_CREATE xTaskCreatePinnedToCore

#endif

