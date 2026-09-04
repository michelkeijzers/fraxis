#include "DiagnosticsManager.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L1_Composition/Context/ServicesContext.hpp"
#include "../L8_Services/Uart/Uart.hpp"
#include "../L9_Utilities/Assert/Assert.hpp"
#include "../L9_Utilities/String/StringUtilities.hpp"
#include <string.h>

DiagnosticsManager::DiagnosticsManager(Context& context)
:   _context(context)
{
}

void DiagnosticsManager::OnTaskData(
    Types::ETaskId taskId, 
    uint64_t timeStamp, 
    uint64_t stackSize)
{
    TaskDataStruct taskData
    {
        static_cast<uint8_t>(taskId),
        timeStamp,
        stackSize
    };

    _context.GetServices().GetUart().Send((const char*)&taskData, sizeof(taskData));
}

void DiagnosticsManager::OnLogEntry(
    Types::ETaskId taskId, 
    uint64_t timeStamp, 
    Types::ELogLevel logLevel,
    const char* text)
{
    Assert::IsNotNullptr(taskId, (void*) text, "text");

    LogEntryStruct logEntry
    {
        static_cast<uint8_t>(taskId),
        timeStamp,
        static_cast<uint8_t>(logLevel),
        {}
    };
    StringUtilities::CopyToBuffer(text, logEntry.text, DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH);
    _context.GetServices().GetUart().Send((const char*)&logEntry, sizeof(logEntry));
}
