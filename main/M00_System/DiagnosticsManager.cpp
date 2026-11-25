#include "DiagnosticsManager.hpp"
#include "../M80_Services/Uart/IUart.hpp"
#include "../M90_Utilities/Assert/IAssert.hpp"
#include "../M90_Utilities/String/StringUtilities.hpp"
#include <string>
#include <chrono>
#include <span>

DiagnosticsManager::DiagnosticsManager(
    M80::Uart::IUart& uart,
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities)
:   
    _uart(uart),
    _assert(assert),
    _stringUtilities(stringUtilities)
{
    // No functionality required.
}

// TODO: Initialize Uart here, not in DiagnoaticsTask, or better: via Diagnostics task

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
    _uart.Send(bytes);
}

void DiagnosticsManager::OnLogEntry(
    Types::ETaskId taskId, 
    std::chrono::microseconds timeStamp,
    Types::ELogLevel logLevel,
    const char* text)
{
    _assert.IsNotNullptr(taskId, text, "text");

    LogEntryStruct logEntry
    {
        static_cast<uint8_t>(taskId),
        timeStamp,
        static_cast<uint8_t>(logLevel),
        {}
    };

    _stringUtilities.CopyToBuffer(
        std::string_view { text }, 
        logEntry.text.data(), 
        DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH);
    
    _uart.Send(std::as_bytes(std::span{ &logEntry, 1 }));
}
