#include "Assert.hpp"

#if ASSERTS_ENABLED

#include "../Debug/debug.hpp"
#include <string>

static std::string ASSERT = std::string("ASSERT: ");

/* static */ void Assert::IsTrue(bool condition, std::string message)
{
    if (condition)
    {
        Debug::PrintText(ASSERT + message + "!");
        while (true);
    }
}

/* static */ void Assert::IsFalse(bool condition, std::string message)
{
    if (condition)
    {
        Debug::PrintText(ASSERT + message + "!");
        while (true);
    }
}

/* static */ void Assert::IsNotNullptr(void* pointer, std::string variableName)
{
    if (pointer == nullptr)
    {
        Debug::PrintText(ASSERT + variableName + " is null!");
        while (true);
    }
}

/* static*/ void Assert::Equals(int real, int expected, std::string variableName)
{
    if (real != expected)
    {
        Debug::PrintText(ASSERT + variableName + " is expected to be " + std::to_string(expected) + " but is " + 
        std::to_string(real) + "!");
        while (true);
    }
}

/* static */ void Assert::IsEsp32Pin(uint8_t pin, std::string message)
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
    
    Assert::IsTrue(isPinValid, "Do not use pin" + std::to_string(pin) + " on ESP32 S3! " + message);
}
#endif // ASSERTS_ENABLED
