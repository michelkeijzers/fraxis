#include "Assert.hpp"

#if ASSERTS_ENABLED

#include "../Log/Log.hpp"
#include <string>

/* static */ std::string Assert::ASSERT = "ASSERT: ";

/* static */ void Assert::Fail(
    Types::ETaskId taskId,
    std::string_view message, 
    std::source_location loc)
{
    Log::Text(
        taskId, 
        std::string( // NOSONAR ESP32 has unrealiable std::format
        loc.file_name()) + ":" + std::to_string(loc.line()), // NOSONAR ESP32 has unrealiable std::format
        Types::ELogLevel::Critical);
    Log::Text(
        taskId, 
        std::string(ASSERT) + std::string(message) + "!", 
        Types::ELogLevel::Critical);
    Halt();
}

/* static */ void Assert::IsTrue(
    Types::ETaskId taskId,
    bool condition, 
    std::string_view message, 
    std::source_location loc)
{
    if (!condition)
    {
        Log::Text(
            taskId, 
            std::string( // NOSONAR ESP32 has unrealiable std::format
            loc.file_name()) + ":" + std::to_string(loc.line()), // NOSONAR ESP32 has unrealiable std::format
            Types::ELogLevel::Critical);
        Log::Text(
            taskId, 
            std::string(ASSERT) + std::string(message) + "!", 
            Types::ELogLevel::Critical);
        Halt();
    }
}

/* static */ void Assert::IsFalse(
    Types::ETaskId taskId,
    bool condition,
    std::string_view message,
    std::source_location loc)
{
    if (condition)
    {
        Log::Text(
            taskId,
            std::string(loc.file_name()) + ":" + std::to_string(loc.line()), // NOSONAR: std::string instead of format
            Types::ELogLevel::Critical);

        Log::Text(
            taskId, 
            std::string(ASSERT) + std::string(message) + "!", 
            Types::ELogLevel::Critical);
        Halt();
    }
}

/* static */ void Assert::IsNotNullptr(
    Types::ETaskId taskId,
    void* pointer, // NOSONAR: meant to handle any type
    std::string_view variableName,
    std::source_location loc)
{
    if (pointer == nullptr)
    {
        Log::Text(
            taskId, 
            std::string(loc.file_name()) + ":" + std::to_string(loc.line()), // NOSONAR ESP32 has unrealiable std::format
            Types::ELogLevel::Critical); 
        Log::Text(
            taskId, 
            std::string(ASSERT) + std::string(variableName) + " is nullptr!", 
            Types::ELogLevel::Critical);
        Halt();
    }
}

/* static */ void Assert::IsEsp32Pin(
    Types::ETaskId taskId,
    uint8_t pin, 
    std::string_view message,
    std::source_location loc)
{
    bool isPinValid = (
        (pin >= 1 && pin <= 2) || // OK for general IO, ADC, RTC
        (pin == 3) || // Strapping pin, boot JTAG source, avoid strong pulls at reset
        (pin >= 4 && pin <= 8) || // OK for general IO, ADC, touch, RTC
                                 // 9-13 often used for SPI flash
                                 // 14 often used for SPI flash/PSRAM
        (pin >= 15 && pin <= 18) || // OK for general IO, ADC, RTC
                                    // 19-20 used for USB/JTAG
                                    // 21 used for OTG 
                                    // 22-25 do not exist
                                    // 26-32 used for internal flash 
                                    // 33 - 37: often used for spi flash/PSRAM 
        (pin >= 38 && pin <= 42) || // OK for general IO (38: check board if tied to flash 
                                    // 43-44 Used for USB-UART
        (pin >= 45 && pin <= 46) || // OK but strapping pin, avoid strong pulls
        (pin >= 47) || // OFten ree, good for LEDs/buttons
        (pin == 48)); // Drives on board RRG bLED on DevKit C-1
        
    if (!isPinValid)
    {
        Log::Text(
            taskId, 
            std::string(loc.file_name()) + ":" + std::to_string(loc.line()),  // NOSONAR: std::string instead of format
            Types::ELogLevel::Critical); 
        Log::Text(
            taskId, 
            std::string(ASSERT) + "Do not use pin" + std::to_string(pin) + "on ESP32 S3! " +  // NOSONAR ESP32 has unrealiable std::format
            std::string(message), Types::ELogLevel::Critical);
        Halt();
    }
}

/* static */ void Assert::Halt()
{
    abort();
    while (true) 
    {
        // Wait forever
    };
}

#endif // ASSERTS_ENABLED
