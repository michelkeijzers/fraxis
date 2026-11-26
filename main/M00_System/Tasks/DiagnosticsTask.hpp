#pragma once

#include "../WatchDog.hpp"
#include "../DiagnosticsManager.hpp"
#include "../Queues/DiagnosticsQueueReader.hpp"
#include "../../M90_Utilities/Task/Task.hpp"

namespace M80::Uart
{
    class IUart;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

class WatchDog;
class RtosTask;
class DiagnosticsQueue;

class DiagnosticsTask : public M90::Task::Task
{
public:
    explicit DiagnosticsTask(
        WatchDog& watchDog,
        DiagnosticsQueueReader& diagnosticsQueueReader,
        M80::Uart::IUart& uart,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

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
    DiagnosticsQueueReader& _diagnosticsQueueReader;

    M80::Uart::IUart& _uart;

    WatchDog& _watchDog;
};
