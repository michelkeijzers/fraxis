#ifdef ESP_PLATFORM

#include "EspI2c.hpp"
#include "driver/i2c.h"
#include "esp_err.h"

EspI2c::EspI2c() 
{
}

EspI2c::~EspI2c() 
{
}

bool EspI2c::IsValidPort(
    uint8_t port)
{
    return (port == I2C_NUM_0) || (port == I2C_NUM_1);
}

bool EspI2c::ParamConfig(
    uint8_t port, 
    uint8_t sdaPin,
    uint8_t sclPin,
    uint32_t frequency)
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = sdaPin;
    conf.scl_io_num = sclPin;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = { frequency };
    return (i2c_param_config(static_cast<i2c_port_t>(port), &conf) == ESP_OK);
}

bool EspI2c::DriverInstall(
    uint8_t port)
{
    return (i2c_driver_install(static_cast<i2c_port_t>(port), I2C_MODE_MASTER, 0, 0, 0) == ESP_OK);
}

bool EspI2c::MasterWriteToDevice(
    uint8_t port, 
    uint8_t deviceAddress,
    const uint8_t *data,
    size_t length, 
    uint32_t timeoutInMs)
{
    return (i2c_master_write_to_device(
        static_cast<i2c_port_t>(port), deviceAddress, data, length, timeoutInMs / portTICK_PERIOD_MS) == ESP_OK);
}

bool EspI2c::MasterReadFromDevice(
    uint8_t port, 
    uint8_t deviceAddress,
    uint8_t *data, 
    size_t length,
    uint32_t timeoutInMs)
{
    return (i2c_master_read_from_device(
        static_cast<i2c_port_t>(port), deviceAddress, data, length, timeoutInMs / portTICK_PERIOD_MS) == ESP_OK);
}

void* EspI2c::CmdLinkCreate()
{
    return i2c_cmd_link_create();
}

void EspI2c::CmdLinkDelete(
    void* cmd)
{
    i2c_cmd_link_delete(cmd);
}

bool EspI2c::MasterStart(
    void* cmd)
{
    return (i2c_master_start(cmd) == ESP_OK);
}

bool EspI2c::MasterWriteDeviceAddress(
    void* cmd,
    uint8_t deviceAddress)
{
    return (i2c_master_write_byte(cmd, (deviceAddress << 1) | I2C_MASTER_WRITE, true) == ESP_OK);
}

bool EspI2c::MasterWriteRegisterAddress(
    void* cmd,
    uint8_t registerAddress)
{
    return (MasterWriteByte(cmd, registerAddress) == ESP_OK);
}

bool EspI2c::MasterWriteByte(
    void* cmd,
    uint8_t byteToWrite)
{
    return (i2c_master_write_byte(cmd, byteToWrite, true) == ESP_OK);
}

bool EspI2c::MasterReadByte(
    void* cmd, 
    uint8_t* byteToRead)
{
    return (i2c_master_read(cmd, byteToRead, 1, I2C_MASTER_LAST_NACK) == ESP_OK);
}

bool EspI2c::MasterWrite(
    void* cmd, 
    const uint8_t *data,
    size_t length)
{
    return (i2c_master_write(cmd, data, length, true) == ESP_OK);
}

bool EspI2c::MasterRead(
    void* cmd,
    uint8_t *data,
    size_t length)
{
    return (i2c_master_read(cmd, data, length, I2C_MASTER_LAST_NACK) == ESP_OK);
}

bool EspI2c::MasterStop(
    void* cmd)
{
    return (i2c_master_stop(cmd) == ESP_OK);
}

bool EspI2c::MasterCmdBegin(
    uint8_t port,
    void* cmd, 
    uint32_t timeoutInMs)
{
    return (i2c_master_cmd_begin(static_cast<i2c_port_t>(port), cmd, timeoutInMs / portTICK_PERIOD_MS) == ESP_OK);
}

#endif // ESP_PLATFORM
