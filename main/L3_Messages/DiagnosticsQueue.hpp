#pragma once

#include "Color.hpp"
#include "Position.hpp"
#include "Types.hpp"
#include "../L3_Messages/Queue.hpp"
#include "../L3_Messages/Types.hpp"

class DiagnosticsQueue : public Queue
{
public:
    const static uint8_t MAX_LOG_ENTRY_TEXT_LENGTH = 100;

    DiagnosticsQueue();
    ~DiagnosticsQueue();
    struct Message
    {
        enum class EType
        {
            HeartBeat,
            TaskData,
            LogEntry
        };

        EType type;

        struct Header
        {
            Types::ETaskId taskId;
            uint64_t timeStamp;
        };

        union 
        {
            struct
            {
                Header header;
            } heartBeat;

            struct
            {
                Header header;
                uint64_t stackSize;
            } taskData;

            struct 
            {
                Header header;
                Types::ELogLevel logLevel;
                char text[DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH]; // NOSONAR: No std::string in queue
            } logEntry;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 1000;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);    
};
