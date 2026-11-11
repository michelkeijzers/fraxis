#pragma once

#include "../WindowsEspErr.hpp"
#include "Gpio.hpp"
#include <chrono>

class WindowsGpio : public Gpio
{
public:
    WindowsGpio();
    ~WindowsGpio() = default;

    esp_err_t ConfigAsOutput(
        uint8_t pin) override;

    esp_err_t ConfigAsInterruptInput(
        uint8_t pin) override;

    esp_err_t SetLevel(
        uint8_t pin,
        bool level) override;

    esp_err_t AddInterruptHandler(
        int pin,
        void (*interruptCallbackFunction)(void*),
        void* arg) override;

    void DelayUs(uint32_t us) override;

private:
    esp_err_t InstallIsrServiceWhenNotInstalledYet() override;

    std::chrono::milliseconds _lastTimeSentTm1637CentralPanel;
    std::chrono::milliseconds _lastTimeSentTm1637Player1;
    std::chrono::milliseconds _lastTimeSentTm1637Player2;
};
