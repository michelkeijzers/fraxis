#include "EspI2c.hpp"

EspI2c::EspI2c(i2c_port_t port, gpio_num_t sda_pin, gpio_num_t scl_pin, uint32_t freq)
    : _i2c_port(port), _sda_pin(sda_pin), _scl_pin(scl_pin), _i2c_freq(freq)
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

esp_err_t EspI2c::ReadRegister(uint8_t devAddr, uint8_t regAddr, uint8_t* data, size_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    // Write register address
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (devAddr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, regAddr, true);

    // Read data
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (devAddr << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, len, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(_i2c_port, cmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t EspI2c::WriteRegister(uint8_t devAddr, uint8_t regAddr, const uint8_t* data, size_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (devAddr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, regAddr, true);
    i2c_master_write(cmd, data, len, true);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(_i2c_port, cmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}
