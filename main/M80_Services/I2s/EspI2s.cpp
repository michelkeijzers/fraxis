#ifdef ESP_PLATFORM

#include "EspI2s.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M30_Messages/Types.hpp"

EspI2s::EspI2s()
: _config(),
  _pinConfig()
{
}

EspI2s::~EspI2s()
{
}

bool EspI2s::ParamConfig(
    uint8_t port,
    uint8_t bclkPin,
    uint8_t wsPin,
    uint8_t dinPin,
    uint8_t doutPin,
    uint32_t sampleRate,
    uint16_t bitsPerSample,
    uint8_t channels)
{
    _config.mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX);
    _config.sample_rate = sampleRate;
    _config.bits_per_sample = static_cast<i2s_bits_per_sample_t>(bitsPerSample);
    _config.channel_format = channels == 1 ? I2S_CHANNEL_FMT_ONLY_LEFT : I2S_CHANNEL_FMT_RIGHT_LEFT;
    _config.communication_format = I2S_COMM_FORMAT_STAND_I2S;
    _config.dma_buf_count = 8;
    _config.dma_buf_len = 1024;
    _config.use_apll = false;
    _config.tx_desc_auto_clear = true;
    _config.fixed_mclk = 0;

    _pinConfig.bck_io_num = bclkPin;
    _pinConfig.ws_io_num = wsPin;
    _pinConfig.data_out_num = doutPin;
    _pinConfig.data_in_num = dinPin;

    return true;
}

bool EspI2s::DriverInstall(
    uint8_t port)
{
    i2s_port_t i2sPort = static_cast<i2s_port_t>(port);
    esp_err_t result = i2s_driver_install(i2sPort, &_config, 0, nullptr);
    if (result != ESP_OK)
    {
        return false;
    }
    result = i2s_set_pin(i2sPort, &_pinConfig);
    return result == ESP_OK;
}

bool EspI2s::Start(
    uint8_t port)
{
    i2s_port_t i2sPort = static_cast<i2s_port_t>(port);
    return i2s_start(i2sPort) == ESP_OK;
}

bool EspI2s::Stop(
    uint8_t port)
{
    i2s_port_t i2sPort = static_cast<i2s_port_t>(port);
    return i2s_stop(i2sPort) == ESP_OK;
}

size_t EspI2s::Read(
    uint8_t port,
    void* buffer,
    size_t length,
    uint32_t timeoutInMs)
{
    i2s_port_t i2sPort = static_cast<i2s_port_t>(port);
    size_t bytesRead = 0;
    esp_err_t result = i2s_read(i2sPort, buffer, length, &bytesRead, portMAX_DELAY);
    if (result != ESP_OK)
    {
        return 0;
    }
    return bytesRead;
}

size_t EspI2s::Write(
    uint8_t port,
    const void* buffer,
    size_t length,
    uint32_t timeoutInMs)
{
    i2s_port_t i2sPort = static_cast<i2s_port_t>(port);
    size_t bytesWritten = 0;
    esp_err_t result = i2s_write(i2sPort, buffer, length, &bytesWritten, portMAX_DELAY);
    if (result != ESP_OK)
    {
        return 0;
    }
    return bytesWritten;
}

bool EspI2s::SetClock(
    uint8_t port,
    uint32_t sampleRate)
{
    i2s_port_t i2sPort = static_cast<i2s_port_t>(port);
    i2s_config_t config = _config;
    config.sample_rate = sampleRate;
    return i2s_set_clk(i2sPort, config.sample_rate, static_cast<i2s_bits_per_sample_t>(_config.bits_per_sample), _config.channel_format) == ESP_OK;
}

#endif // ESP_PLATFORM
