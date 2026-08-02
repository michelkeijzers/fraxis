#include "../../L0_System/DeviceSettings.hpp"
#include "../../L6_DeviceDrivers/I2cTaskDeviceDriversDelegate.hpp"
#include "../../L7_WindowsGdi/GdiSimulator.hpp"
#include "../../L9_Utilities/Time/TimeUtilities.hpp"
#include "WindowsGpio.hpp"
#include "windows.h"

WindowsGpio::WindowsGpio()
:   _lastTimeSentTm1637CentralPanel(0), 
    _lastTimeSentTm1637Player1(0), 
    _lastTimeSentTm1637Player2(0)
{
}

WindowsGpio::~WindowsGpio()
{
}

bool WindowsGpio::ConfigAsOutput(uint8_t pin)
{
    return true;
}

bool WindowsGpio::ConfigAsInterruptInput(uint8_t pin)
{
    return true;
}

/// @brief Sends message to Gdi Simulator.
/// @details To prevent too many post messages to be sent, it will only sent at a maximum frequency as the 
/// refresh frequency. This will work because it does not matter what exactly has been sent by the pins as
/// the GDI simulator always updates the entire control.
/// The update times will be kept per item (e.g. three different times for the TM1637's.
bool WindowsGpio::SetLevel(uint8_t pin, bool level)
{
    switch (pin)
    {
    case DeviceSettings::PIN_TM1637_CENTRAL_PANEL_DATA:
    {
        uint64_t now = TimeUtilities::GetCurrentTimeInUs();
        uint64_t timeToElapse = TimeUtilities::FrequencyToIntervalUs(
            I2cTaskDeviceDriversDelegate::TM1637_WRITE_DISPLAY_FREQUENCY);
        if (now >= _lastTimeSentTm1637CentralPanel + timeToElapse)
        {
            PostMessage(simulatorContext.hWndMain, WM_TM1637_CENTRAL_PANEL_UPDATE, 0, 0);
        }
    }
    break;
    
    case DeviceSettings::PIN_TM1637_PLAYER_1_DATA:
    {
        uint64_t now = TimeUtilities::GetCurrentTimeInUs();
        uint64_t timeToElapse = TimeUtilities::FrequencyToIntervalUs(
            I2cTaskDeviceDriversDelegate::TM1637_WRITE_DISPLAY_FREQUENCY);
        if (now >= _lastTimeSentTm1637Player1 + timeToElapse)
        {
            PostMessage(simulatorContext.hWndMain, WM_TM1637_PLAYER1_UPDATE, 0, 0);
        }
    }
    break;

    case DeviceSettings::PIN_TM1637_PLAYER_2_DATA:
    {
        uint64_t now = TimeUtilities::GetCurrentTimeInUs();
        uint64_t timeToElapse = TimeUtilities::FrequencyToIntervalUs(
            I2cTaskDeviceDriversDelegate::TM1637_WRITE_DISPLAY_FREQUENCY);
        if (now >= _lastTimeSentTm1637Player2 + timeToElapse)
        {
            PostMessage(simulatorContext.hWndMain, WM_TM1637_PLAYER2_UPDATE, 0, 0);
        }
    }
    break;

    default:
        // Ignore others.
        break;
    }
    return true;
}


bool WindowsGpio::InstallIsrServiceWhenNotInstalledYet()
{
    return true;
}

bool WindowsGpio::AddInterruptHandler(int pin, void (*interruptCallbackFunction)(void*), void* arg)
{
    return true;
}

void WindowsGpio::DelayUs(uint32_t us)
{
    // Ignore us delay.
}