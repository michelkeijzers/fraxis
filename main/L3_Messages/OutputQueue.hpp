#pragma once

#include "Types.hpp"
#include "../L2_Applications/Queues/Queue.hpp"
#include "../L4_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"

class OutputQueue : public Queue
{
public:
    OutputQueue();
    ~OutputQueue();

    struct OutputMessage
    {
        enum class EType
        {
            Led,
            Lcd2004Line
        };

        EType type;

        union 
        {
            struct
            {
                Types::ELedId ledId;
                bool state;
            };
            struct
            {
                uint8_t lineNumber;
                char lineContent[Lcd2004::LINE_WIDTH];
            } lcd2004Line;
        };
    };
};
