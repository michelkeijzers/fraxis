#pragma once

#include "Gpio.hpp"
#include <chrono>

class WindowsGpio : public Gpio
{
public:
    WindowsGpio();
    ~WindowsGpio() = default;

    bool ConfigAsOutput(
        uint8_t pin) override;
    bool ConfigAsInterruptInput(
        uint8_t pin) override;
    bool SetLevel(
        uint8_t pin,
        bool level) override;

    bool AddInterruptHandler(
        int pin,
        void (*interruptCallbackFunction)(void*),
        void* arg) override;

    void DelayUs(uint32_t us) override;

private:
    bool InstallIsrServiceWhenNotInstalledYet() override;

    std::chrono::milliseconds _lastTimeSentTm1637CentralPanel;
    std::chrono::milliseconds _lastTimeSentTm1637Player1;
    std::chrono::milliseconds _lastTimeSentTm1637Player2;
};
