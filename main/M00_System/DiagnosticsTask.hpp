#pragma once

#include "WatchDog.hpp"
#include "DiagnosticsManager.hpp"
#include "Queues/DiagnosticsQueueReader.hpp"
#include "../M90_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class DiagnosticsQueue;

class DiagnosticsTask : public Task
{
public:
    explicit DiagnosticsTask(
        Context& context);
    ~DiagnosticsTask() = default;

    void Initialize() override;
    void Run() override;
    static void TaskEntry(
        void* param);

private:
    Context& _context;

    DiagnosticsQueue& _diagnosticsQueue;
    DiagnosticsQueueReader _diagnosticsQueueReader;

    DiagnosticsManager _diagnosticsManager;
    WatchDog _watchDog;
};
