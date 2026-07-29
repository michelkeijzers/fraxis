#pragma once

#include "../../L3_Messages/I2cOutputQueue.hpp"
#include <cstdint>
#include <string>

class QueueWriters;

class Send
{
public:
    Send(QueueWriters& queueWriters);
    ~Send();

    /// @defgroup I2C @{
    ///   @defgroup MCP23017 @{
    void Led(Types::ELedId ledId, bool state);
    ///   @} MCP23017

    ///   @defgroup LCD2004 @{
    void Line(uint8_t lineNumber, std::string_view line);
    ///   @} LCD2004
    /// @} I2C
    
    /// @defgroup TM1637 @{
    void Value(Types::ETm1637Id tm1637Id, uint32_t value);
    void Time(Types::ETm1637Id tm1637Id, uint8_t first, uint8_t second);
    /// @} TM1637

    /// @defgroup LedStrips @{
    void Pixel(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue);
    // void Fill(uint8_t red, uint8_t green, uint8_t blue);
    /// @} LedStrips

private:
    QueueWriters& _queueWriters;
};
