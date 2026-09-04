#include "DiagnosticsQueueWriter.hpp"
#include "../../L3_Messages/DiagnosticsQueue.hpp"
#include "../../L3_Messages/Types.hpp"
#include "../../L4_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../L9_Utilities/String/StringUtilities.hpp"
#include <cstring>

DiagnosticsQueueWriter::DiagnosticsQueueWriter(
    DiagnosticsQueue& diagnosticsQueue )
{
    SetQueue(diagnosticsQueue);
}

DiagnosticsQueue& DiagnosticsQueueWriter::GetDiagnosticsQueue() 
{
    return static_cast<DiagnosticsQueue&>(GetQueue());  
}

void DiagnosticsQueueWriter::SendHeartBeat(
    Types::ETaskId taskId, 
    uint64_t timeStamp)
{
    DiagnosticsQueue::Message message;
    message.type = DiagnosticsQueue::Message::EType::HeartBeat;
    message.heartBeat.header.taskId = taskId;
    message.heartBeat.header.timeStamp = timeStamp;
    GetDiagnosticsQueue().GetRtosQueue().Send(&message, 0);
}

void DiagnosticsQueueWriter::SendTaskData(
    Types::ETaskId taskId, 
    uint64_t timeStamp,
    uint64_t stackSize)
{
    DiagnosticsQueue::Message message;
    message.type = DiagnosticsQueue::Message::EType::TaskData;
    message.taskData.header.taskId = taskId;
    message.taskData.header.timeStamp = timeStamp;
    message.taskData.stackSize = stackSize;
    GetDiagnosticsQueue().GetRtosQueue().Send(&message, 0);
}

void DiagnosticsQueueWriter::SendLogEntry(
    Types::ETaskId taskId, 
    uint64_t timeStamp,
    Types::ELogLevel logLevel,
    const char* text)
{
    DiagnosticsQueue::Message message;
    message.type = DiagnosticsQueue::Message::EType::LogEntry;
    message.logEntry.header.taskId = taskId;
    message.logEntry.header.timeStamp = timeStamp;
    message.logEntry.logLevel = logLevel;
    StringUtilities::CopyToBuffer(text, message.logEntry.text, DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH);
    message.logEntry.text[DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH - 1] = '\0';
    GetDiagnosticsQueue().GetRtosQueue().Send(&message, 0);
}