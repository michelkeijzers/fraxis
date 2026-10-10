#ifdef ESP_PLATFORM

#include "EspPwm.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M30_Messages/Types.hpp"

EspPwm::EspPwm()
: _channel(LEDC_CHANNEL_0),
  _pin(0),
  _frequency(0),
  _dutyCycle(0.0f),
  _started(false)
{
}

EspPwm::~EspPwm()
{
    Stop();
}

bool EspPwm::Config(
    uint8_t pin,
    uint32_t frequency,
    float dutyCycle)
{
    _pin = pin;
    _frequency = frequency;
    _dutyCycle = dutyCycle;

    ledc_timer_config_t timerConfig = {};
    timerConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    timerConfig.duty_resolution = LEDC_TIMER_13_BIT;
    timerConfig.freq_hz = frequency;
    timerConfig.timer_num = LEDC_TIMER_0;

    esp_err_t result = ledc_timer_config(&timerConfig);
    if (result != ESP_OK)
    {
        return false;
    }

    ledc_channel_config_t channelConfig = {};
    channelConfig.gpio_num = pin;
    channelConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    channelConfig.channel = _channel;
    channelConfig.intr_type = LEDC_INTR_DISABLE;
    channelConfig.timer_sel = LEDC_TIMER_0;
    channelConfig.duty = static_cast<uint32_t>((1 << 13) * dutyCycle);
    channelConfig.hpoint = 0;

    result = ledc_channel_config(&channelConfig);
    return result == ESP_OK;
}

bool EspPwm::Start()
{
    if (_started)
    {
        return true;
    }
    _started = true;
    return true;
}

bool EspPwm::Stop()
{
    if (!_started)
    {
        return true;
    }
    esp_err_t result = ledc_stop(LEDC_LOW_SPEED_MODE, _channel, 0);
    _started = false;
    return result == ESP_OK;
}

bool EspPwm::SetFrequency(
    uint32_t frequency)
{
    if (_frequency == frequency)
    {
        return true;
    }
    _frequency = frequency;
    ledc_timer_config_t timerConfig = {};
    timerConfig.speed_mode = LEDC_LOW_SPEED_MODE;
    timerConfig.duty_resolution = LEDC_TIMER_13_BIT;
    timerConfig.freq_hz = frequency;
    timerConfig.timer_num = LEDC_TIMER_0;
    return ledc_timer_config(&timerConfig) == ESP_OK;
}

bool EspPwm::SetDutyCycle(
    float dutyCycle)
{
    if (_dutyCycle == dutyCycle)
    {
        return true;
    }
    _dutyCycle = dutyCycle;
    return ledc_set_duty(LEDC_LOW_SPEED_MODE, _channel, static_cast<uint32_t>((1 << 13) * dutyCycle)) == ESP_OK;
}

#endif // ESP_PLATFORM
