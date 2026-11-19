#pragma once

#include "WatchDog.hpp"
#include "DiagnosticsManager.hpp"
#include "Queues/DiagnosticsQueueReader.hpp"
#include "../M90_Utilities/Task/Task.hpp"

namespace M90::Assert
{
    class IAssert;
}

class Context;
class RtosTask;
class DiagnosticsQueue;

class DiagnosticsTask : public M90::Task::Task
{
public:
    explicit DiagnosticsTask(
        Context& context,
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities);

    DiagnosticsTask(
        const DiagnosticsTask&) = delete;

    DiagnosticsTask& operator=(
        const DiagnosticsTask&) = delete;

    DiagnosticsTask(
        DiagnosticsTask&&) = delete;

    DiagnosticsTask& operator=(
        DiagnosticsTask&&) = delete;

    ~DiagnosticsTask() override = default;

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
