
#pragma once

#ifdef ESP_PLATFORM
#include "esp_err.h"
#else
#include  "../WindowsEspErr.hpp"
#endif 

#include <cstdint>

class Gpio
{
public:
    Gpio() = default;

    Gpio(
        const Gpio&) = delete;
    Gpio& operator=(
        const Gpio&) = delete;
    Gpio(
        Gpio&&) = delete;
    Gpio& operator=(
        Gpio&&) = delete;

    virtual ~Gpio() = default;

    virtual esp_err_t ConfigAsOutput(
        uint8_t pin) = 0;

    virtual esp_err_t ConfigAsInterruptInput(
        uint8_t pin) = 0;

    virtual esp_err_t SetLevel(
        uint8_t pin, 
        bool level) = 0;

    esp_err_t InstallIsrService();

    virtual esp_err_t AddInterruptHandler(
        int pin,
        void (*interruptCallbackFunction)(void*),
        void* arg) = 0;

    virtual void DelayUs(
        uint32_t microSeconds) = 0;

protected:
    virtual esp_err_t InstallIsrServiceWhenNotInstalledYet() = 0;

private:
    static bool _isIsrServiceInstalled;
};
