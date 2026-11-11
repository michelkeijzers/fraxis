#include "Gpio.hpp"

/* static */ bool Gpio::_isIsrServiceInstalled = false;

esp_err_t Gpio::InstallIsrService()
{
    if (!_isIsrServiceInstalled)
    {
        esp_err_t result = InstallIsrServiceWhenNotInstalledYet();
        if (result == ESP_OK)
        {
            _isIsrServiceInstalled = true;
            return ESP_OK;
        }
        return result;
    }
    return ESP_OK;
}
