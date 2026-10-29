#include "DiagnosticsManager.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M10_Composition/Context/ServicesContext.hpp"
#include "../M80_Services/Uart/Uart.hpp"
#include "../M90_Utilities/Assert/Assert.hpp"
#include "../M90_Utilities/String/StringUtilities.hpp"
#include <string>
#include <chrono>
#include <span>

DiagnosticsManager::DiagnosticsManager(Context& context)
:   _context(context)
{
}
void DiagnosticsManager::OnTaskData(
    Types::ETaskId taskId, 
    std::chrono::microseconds timeStamp,
    uint32_t stackSize)
{
    TaskDataStruct taskData
    {
        static_cast<uint8_t>(taskId),
        timeStamp,
        stackSize
    };
    
    auto bytes = std::as_bytes(std::span{ &taskData, 1 });
    _context.GetServices().GetUart().Send(bytes);
}

void DiagnosticsManager::OnLogEntry(
    Types::ETaskId taskId, 
    std::chrono::microseconds timeStamp,
    Types::ELogLevel logLevel,
    const char* text)
{
    Assert::IsNotNullptr(taskId, static_cast<const void*>(text), "text");

    LogEntryStruct logEntry
    {
        static_cast<uint8_t>(taskId),
        timeStamp,
        static_cast<uint8_t>(logLevel),
        {}
    };

    StringUtilities::CopyToBuffer(
        std::string_view { text }, 
        logEntry.text.data(), 
        DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH);
    
    _context.GetServices().GetUart().Send(std::as_bytes(std::span{ &logEntry, 1 }));
}
