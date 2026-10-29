#pragma once

#include "../LedStrips/Color.hpp"
#include "../LedStrips/Position.hpp"
#include "../Types.hpp"
#include "../Queue.hpp"
#include "../../M30_Messages/Diagnostics/DiagnosticsQueue.hpp"
#include <chrono>
#include <array>

class DiagnosticsQueue : public Queue
{
public:
    const static uint8_t MAX_LOG_ENTRY_TEXT_LENGTH = 100;

    DiagnosticsQueue() = default;

    DiagnosticsQueue(const DiagnosticsQueue&) = delete;
    DiagnosticsQueue& operator=(const DiagnosticsQueue&) = delete;
    DiagnosticsQueue(DiagnosticsQueue&&) = delete;
    DiagnosticsQueue& operator=(DiagnosticsQueue&&) = delete;

    ~DiagnosticsQueue() override = default;

    struct Message
    {
        enum class EType : uint8_t
        {
            HeartBeat,
            TaskData,
            LogEntry
        };

        EType type = EType::HeartBeat;

        struct Header
        {
            Types::ETaskId taskId = Types::ETaskId::ApplicationsTask;
            std::chrono::microseconds timeStamp = {};
        };

        union 
        {
            struct
            {
                Header header = {};
            } heartBeat;

            struct
            {
                Header header = {};
                uint32_t stackSize = 0;
            } taskData;

            struct 
            {
                Header header = {};
                Types::ELogLevel logLevel = Types::ELogLevel::Debug;
                std::array<char, DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH> text = {};
            } logEntry;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 1000;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);    
};
