#include "../../M00_System/DeviceSettings.hpp"
#include "../../M60_DeviceDrivers/I2cTaskDeviceDriversDelegate.hpp"
#include "../../M70_WindowsGdi/GdiSimulator.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"
#include "WindowsGpio.hpp"
#include "windows.h" // NOSONAR S3806 non portable path

WindowsGpio::WindowsGpio()
:   _lastTimeSentTm1637CentralPanel(0), 
    _lastTimeSentTm1637Player1(0), 
    _lastTimeSentTm1637Player2(0)
{
}

bool WindowsGpio::ConfigAsOutput(
    uint8_t /* pin */)
{
    return true;
}

bool WindowsGpio::ConfigAsInterruptInput(
    uint8_t /* pin */)
{
    return true;
}

/// @brief Sends message to Gdi Simulator.
/// @details To prevent too many post messages to be sent, it will only sent at a maximum frequency
/// as the refresh frequency. This will work because it does not matter what exactly has been sent 
/// by the pins as the GDI simulator always updates the entire control.
/// The update times will be kept per item (e.g. three different times for the TM1637's.
bool WindowsGpio::SetLevel(
    uint8_t pin,
    bool /* level */)
{
    switch (pin)
    {
    case DeviceSettings::PIN_TM1637_CENTRAL_PANEL_DATA:
    {
        std::chrono::microseconds now = TimeUtilities::GetCurrentTimeInUs();
        std::chrono::microseconds timeToElapse = TimeUtilities::FrequencyToIntervalUs(
            I2cTaskDeviceDriversDelegate::TM1637_WRITE_DISPLAY_FREQUENCY);
        if (now >= _lastTimeSentTm1637CentralPanel + timeToElapse)
        {
            PostMessage(simulatorContext.hWndMain, WM_TM1637_CENTRAL_PANEL_UPDATE, 0, 0);
        }
    }
    break;
    
    case DeviceSettings::PIN_TM1637_PLAYER_1_DATA:
    {
        std::chrono::microseconds now = TimeUtilities::GetCurrentTimeInUs();
        std::chrono::microseconds timeToElapse = TimeUtilities::FrequencyToIntervalUs(
            I2cTaskDeviceDriversDelegate::TM1637_WRITE_DISPLAY_FREQUENCY);
        if (now >= _lastTimeSentTm1637Player1 + timeToElapse)
        {
            PostMessage(simulatorContext.hWndMain, WM_TM1637_PLAYER1_UPDATE, 0, 0);
        }
    }
    break;

    case DeviceSettings::PIN_TM1637_PLAYER_2_DATA:
    {
        std::chrono::microseconds now = TimeUtilities::GetCurrentTimeInUs();
        std::chrono::microseconds timeToElapse = TimeUtilities::FrequencyToIntervalUs(
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

bool WindowsGpio::AddInterruptHandler(
    int /* pin */,
    void (* /* interruptCallbackFunction */)(void*), // NOSONAR S5008: void more meaningful name
    void* /* arg */) // NOSONAR: S5008: void *
{
    return true;
}

void WindowsGpio::DelayUs(
    uint32_t /* us */)
{
    // Ignore us delay.
}