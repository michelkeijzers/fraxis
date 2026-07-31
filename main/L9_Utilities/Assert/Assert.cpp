#include "Assert.hpp"

#if ASSERTS_ENABLED

#include "../Debug/debug.hpp"
#include <string>

static std::string ASSERT = "ASSERT: ";

/* static */ void Assert::Fail(std::string_view message, std::source_location loc)
{
    Debug::PrintText(std::string(loc.file_name()) + ":" + std::to_string(loc.line()));
    Debug::PrintText(ASSERT + std::string(message) + "!");
    Halt();
}

/* static */ void Assert::IsTrue(bool condition, std::string_view message, std::source_location loc)
{
    if (condition)
    {
        Debug::PrintText(std::string(loc.file_name()) + ":" + std::to_string(loc.line()));
        Debug::PrintText(std::string(ASSERT) + std::string(message) + "!");
        Halt();
    }
}

/* static */ void Assert::IsFalse(bool condition, std::string_view message, std::source_location loc)
{
    if (condition)
    {
        Debug::PrintText(std::string(loc.file_name()) + ":" + std::to_string(loc.line()));
        Debug::PrintText(std::string(ASSERT) + std::string(message) + "!");
        Halt();
    }
}

/* static */ void Assert::IsNotNull(void* pointer, std::string_view variableName, std::source_location loc)
{
    if (pointer == NULL)
    {
        Debug::PrintText(std::string(loc.file_name()) + ":" + std::to_string(loc.line()));
        Debug::PrintText(std::string(ASSERT) + std::string(variableName) + " is nullptr!");
        Halt();
    }
}

/* static */ void Assert::IsNotNullptr(void* pointer, std::string_view variableName, std::source_location loc)
{
    if (pointer == nullptr)
    {
        Debug::PrintText(std::string(loc.file_name()) + ":" + std::to_string(loc.line()));
        Debug::PrintText(std::string(ASSERT) + std::string(variableName) + " is nullptr!");
        Halt();
    }
}

/* static*/ void Assert::Equals(int real, int expected, std::string_view variableName, std::source_location loc)
{
    if (real != expected)
    {
        Debug::PrintText(std::string(loc.file_name()) + ":" + std::to_string(loc.line()));
        Debug::PrintText(std::string(ASSERT) + std::string(variableName) + " is expected to be " + 
            std::to_string(expected) + " but is " + std::to_string(real) + "!");
        Halt();
    }
}

/* static*/ void Assert::NotEquals(int real, int expected, std::string_view variableName, std::source_location loc)
{
    if (real == expected)
    {
        Debug::PrintText(std::string(loc.file_name()) + ":" + std::to_string(loc.line()));
        Debug::PrintText(std::string(ASSERT) + std::string(variableName) + " is not expected to be " + 
            std::to_string(expected) + "!");
        Halt();
    }
}

/* static*/ void Assert::IsNot0(int real, std::string_view variableName, std::source_location loc)
{
    Assert::NotEquals(real, 0, variableName);
}

/* static */ void Assert::IsEsp32Pin(uint8_t pin, std::string_view message, std::source_location loc)
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
        Debug::PrintText(std::string(loc.file_name()) + ":" + std::to_string(loc.line()));
        Debug::PrintText(std::string(ASSERT) + "Do not use pin" + std::to_string(pin) + "on ESP32 S3! " + 
            std::string(message));
        Halt();
    }
}

/* static */ void Assert::Halt()
{
    while (true) {};
}

#endif // ASSERTS_ENABLED
