#pragma once

#include "../../M30_Messages/I2c/I2cOutputQueue.hpp"
#include <cstdint>
#include <string>

class QueueWriters;

class Send
{
public:
    explicit Send();

    Send(const Send&) = delete;
    Send& operator=(const Send&) = delete;
    Send(Send&&) = delete;
    Send& operator=(Send&&) = delete;

    ~Send() = default;

    /// @defgroup I2C @{
    ///   @defgroup MCP23017 @{
    
    void SetQueueWriters(
        QueueWriters& queueWriters);

    void Led(
        Types::ELedId ledId, bool state);
    
    ///   @} MCP23017

    ///   @defgroup LCD2004 @{
    
    void PredefinedCharacter(
        uint8_t slotIndex,
        uint8_t predefinedCharacterIndex);
    
    void CustomCharacter(
        uint8_t slotIndex,
        std::array<uint8_t, Lcd2004::CUSTOM_CHARACTER_DATA_LENGTH> data);
    
    void Line(
        uint8_t lineNumber, std::string_view line);
    
    ///   @} LCD2004
    /// @} I2C
    
    /// @defgroup TM1637 @{

    void Tm1637Enable(
        Types::ETm1637Id tm1637Id,
        bool enable);

    void Tm1637Brightness(
        Types::ETm1637Id tm1637Id,
        uint8_t brightness);
        
    void Value(
        Types::ETm1637Id tm1637Id, 
        uint32_t value);

    void Time(
        Types::ETm1637Id tm1637Id, 
        uint8_t first, 
        uint8_t second);
    
    /// @} TM1637

    /// @defgroup LedStrips @{
    
    void LedStripsBrightness(
    uint8_t brightness);

    void Pixel(
        uint8_t x_position, 
        uint8_t y_position, 
        uint8_t red, 
        uint8_t green, 
        uint8_t blue);
    
    void FrameReady();
    
    /// @} LedStrips

    /// @defgroup MicroSdCard @{
    
    // NOSONAR TODO SPI

    // @} MicroSdCard

private:
    QueueWriters* _queueWriters;
};
