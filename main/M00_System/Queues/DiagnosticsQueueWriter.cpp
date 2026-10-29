#include "DiagnosticsQueueWriter.hpp"
#include "../../M30_Messages/Diagnostics/DiagnosticsQueue.hpp"  
#include "../../M30_Messages/Types.hpp"
#include "../../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../M90_Utilities/String/StringUtilities.hpp"
#include <cstring>

DiagnosticsQueueWriter::DiagnosticsQueueWriter(
    DiagnosticsQueue& diagnosticsQueue )
{
    SetQueue(diagnosticsQueue);
}

DiagnosticsQueue& DiagnosticsQueueWriter::GetDiagnosticsQueue() 
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-static-cast-downcast)
    return static_cast<DiagnosticsQueue&>(GetQueue());  
}

void DiagnosticsQueueWriter::SendHeartBeat(
    Types::ETaskId taskId, 
    std::chrono::microseconds timeStamp)
{
    DiagnosticsQueue::Message message = {};
    message.type = DiagnosticsQueue::Message::EType::HeartBeat;
    // NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)
    message.heartBeat.header.taskId = taskId;
    message.heartBeat.header.timeStamp = timeStamp;
    // NOLINTEND(cppcoreguidelines-pro-type-union-access)
    GetDiagnosticsQueue().GetRtosQueue().Send(&message, 0);
}

void DiagnosticsQueueWriter::SendTaskData(
    Types::ETaskId taskId, 
    std::chrono::microseconds timeStamp,
    uint32_t stackSize)
{
    DiagnosticsQueue::Message message = {};
    message.type = DiagnosticsQueue::Message::EType::TaskData;
    // NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)
    message.taskData.header.taskId = taskId;
    message.taskData.header.timeStamp = timeStamp;
    message.taskData.stackSize = stackSize;
    // NOLINTEND(cppcoreguidelines-pro-type-union-access)
    GetDiagnosticsQueue().GetRtosQueue().Send(&message, 0);
}

void DiagnosticsQueueWriter::SendLogEntry(
    Types::ETaskId taskId, 
    std::chrono::microseconds timeStamp,
    Types::ELogLevel logLevel,
    const char* text)
{
    DiagnosticsQueue::Message message = {};
    message.type = DiagnosticsQueue::Message::EType::LogEntry;
    // NOLINTBEGIN(cppcoreguidelines-pro-type-union-access)
    message.logEntry.header.taskId = taskId;
    message.logEntry.header.timeStamp = timeStamp;
    message.logEntry.logLevel = logLevel;

    StringUtilities::CopyToBuffer(
        std::string_view { text },
        message.logEntry.text.data(),
        static_cast<size_t>(DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH));

    message.logEntry.text[DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH - 1] = '\0';
    // NOLINTEND(cppcoreguidelines-pro-type-union-access)
    GetDiagnosticsQueue().GetRtosQueue().Send(&message, 0);
}
