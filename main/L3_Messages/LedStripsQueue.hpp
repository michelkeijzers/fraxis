#pragma once

#include "Color.hpp"
#include "Position.hpp"
#include "../L3_Messages/Queue.hpp"

class LedStripsQueue : public Queue
{
public:
    LedStripsQueue();
    ~LedStripsQueue();
    struct LedStripsMessage
    {
        enum class EType
        {
            Pixel,
        };

        EType type;

        union 
        {
            /// @brief Position and color
            /// @details Position and Color are not allowed in a union because it deletes the constructor. 
            /// Other options are unwanted, such as std::variant or not using unions.
            struct
            {
                uint8_t x;
                uint8_t y;
                uint8_t red;
                uint8_t green;
                uint8_t blue;
            } pixel;
        };
    };
};
