#include "DiagnosticsQueueReader.hpp"
#include "../DiagnosticsManager.hpp"
#include "../WatchDog.hpp"
#include "../../L3_Messages/DiagnosticsQueue.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

DiagnosticsQueueReader::DiagnosticsQueueReader(
    DiagnosticsQueue& diagnosticsQueue, 
    WatchDog& watchDog, 
    DiagnosticsManager& diagnosticsManager)
: 
    _watchDog(watchDog), 
    _diagnosticsManager(diagnosticsManager)
{
    SetQueue(diagnosticsQueue);
}

DiagnosticsQueue& DiagnosticsQueueReader::GetDiagnosticsQueue()
{
    return static_cast<DiagnosticsQueue&>(GetQueue());
}

bool DiagnosticsQueueReader::HandleMessage() 
{
    bool handled = false;

    if (DiagnosticsQueue::Message message{}; GetDiagnosticsQueue().GetRtosQueue().Receive(&message, 0))
    {
        switch (message.type)
        {
            case DiagnosticsQueue::Message::EType::HeartBeat:
                _watchDog.OnHeartBeat(message.heartBeat.header.taskId, message.heartBeat.header.timeStamp);
                break;

            case DiagnosticsQueue::Message::EType::TaskData:
                _diagnosticsManager.OnTaskData(
                    message.taskData.header.taskId, message.taskData.header.timeStamp, message.taskData.stackSize);
                break;

            case DiagnosticsQueue::Message::EType::LogEntry:
                _diagnosticsManager.OnLogEntry(
                    message.logEntry.header.taskId, 
                    message.logEntry.header.timeStamp,
                    message.logEntry.logLevel, 
                    message.logEntry.text);
                break;

            default:
                Assert::Fail(Types::ETaskId::DiagnosticsTask, "Unknown message type");
                break;
        }
        handled = true;
    }
    return handled;
}
