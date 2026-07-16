#pragma once

#include "i2c.hpp"
#include "driver/i2c.h"

class EspI2c : public I2c
{
public:
    EspI2c(i2c_port_t port, gpio_num_t sda_pin, gpio_num_t scl_pin, uint32_t freq);
    
    void Initialize() override;

    void Write(uint8_t addr, const uint8_t* data, size_t len) override;
    void Read(uint8_t addr, uint8_t* data, size_t len) override;

    void ReadRegister(uint8_t devAddr, uint8_t regAddr, uint8_t* data, size_t len) override;
    void WriteRegister(uint8_t devAddr, uint8_t regAddr, const uint8_t* data, size_t len) override;

private:
    i2c_port_t _i2c_port;
    gpio_num_t _sda_pin;
    gpio_num_t _scl_pin;
    uint32_t _i2c_freq;
};
