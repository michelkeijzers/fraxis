#ifdef ESP_PLATFORM

#include "EspPwm.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M30_Messages/Types.hpp"

EspPwm::EspPwm()
: 
    _channel(LEDC_CHANNEL_0)
{
}

EspPwm::~EspPwm()
{
    Stop();
}

esp_err_t EspPwm::ConfigTimer()
{
    ledc_timer_config_t timerConfig = {};
    timerConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    timerConfig.duty_resolution = LEDC_TIMER_13_BIT;
    timerConfig.freq_hz = GetFrequency();
    timerConfig.timer_num = LEDC_TIMER_0;

    esp_err_t result = ledc_timer_config(&timerConfig);
    if (result == ESP_OK)
    {
        ledc_channel_config_t channelConfig = {};
        channelConfig.gpio_num = GetPin();
        channelConfig.speed_mode = LEDC_LOW_SPEED_MODE;
        channelConfig.channel = _channel;
        channelConfig.intr_type = LEDC_INTR_DISABLE;
        channelConfig.timer_sel = LEDC_TIMER_0;
        channelConfig.duty = static_cast<uint32_t>((1 << 13) * GetDutyCycle());
        channelConfig.hpoint = 0;

        result = ledc_channel_config(&channelConfig);
    }

    return result;
}

esp_err_t EspPwm::LedcStop()
{
    return ledc_stop(LEDC_LOW_SPEED_MODE, _channel, 0);
}

esp_err_t EspPwm::AdjustFrequency()
{
    ledc_timer_config_t timerConfig = {};
    timerConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    timerConfig.duty_resolution = LEDC_TIMER_13_BIT;
    timerConfig.freq_hz = GetFrequency();
    timerConfig.timer_num = LEDC_TIMER_0;
    return ledc_timer_config(&timerConfig);
}

esp_err_t EspPwm::AdjustDutyCycle()
{
    return ledc_set_duty(
        LEDC_LOW_SPEED_MODE, _channel, static_cast<uint32_t>((1 << 13) * GetDutyCycle()));
}

#endif // ESP_PLATFORM
