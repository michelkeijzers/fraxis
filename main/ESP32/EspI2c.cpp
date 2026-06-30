#include "EspI2c.hpp"

EspI2c::EspI2c(i2c_port_t port, gpio_num_t sda_pin, gpio_num_t scl_pin, uint32_t freq)
    : _i2c_port(port), _sda_pin(sda_pin), _scl_pin(scl_pin), _i2c_freq(freq)
{
}

EspI2c::~EspI2c()
{
}

void EspI2c::Init()
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = _sda_pin;
    conf.scl_io_num = _scl_pin;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = _i2c_freq;
    i2c_param_config(_i2c_port, &conf);
    i2c_driver_install(_i2c_port, conf.mode, 0, 0, 0);
}

esp_err_t EspI2c::Write(uint8_t addr, const uint8_t* data, size_t len)
{
    return i2c_master_write_to_device(
        _i2c_port,
        addr,
        data,
        len,
        1000 / portTICK_PERIOD_MS
    );
}
