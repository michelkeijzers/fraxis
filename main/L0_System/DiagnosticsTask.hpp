#pragma once

#include "../L0_System/WatchDog.hpp"
#include "../L0_System/DiagnosticsManager.hpp"
#include "../L0_System/Queues/DiagnosticsQueueReader.hpp"
#include "../L9_Utilities/Task/Task.hpp"

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
