#ifdef ESP_PLATFORM

#include "EspI2cDeviceDriver.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

EspI2cDeviceDriver::EspI2cDeviceDriver()
{
}

EspI2cDeviceDriver::~EspI2cDeviceDriver()
{
}

void EspI2cDeviceDriver::AssertValidPort(uint8_t port)
{
    Assert::IsTrue(port == I2C_NUM_0 || port == I2C_NUM_1, "i2c Port should be I2C_NUM_0 or I2C_NUM_1");
}

void EspI2cDeviceDriver::Initialize()
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = GetSdaPin();
    conf.scl_io_num = GetSclPin();
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = GetFrequency();
    Assert::Equals(i2c_param_config(GetPort(), &conf), ESP_OK, "Failed to configure I2C param config");
    Assert::Equals(i2c_driver_install(GetPort(), conf.mode, 0, 0, 0), ESP_OK, "Failed to install I2C driver");
    MarkInitialized();
}
    
i2c_port_t EspI2cDeviceDriver::GetPort() const
{
    return static_cast<i2c_port_t>(I2cDeviceDriver::GetPort());
}

gpio_num_t EspI2cDeviceDriver::GetSdaPin() const
{
    return static_cast<gpio_num_t>(I2cDeviceDriver::GetSdaPin());
}

gpio_num_t EspI2cDeviceDriver::GetSclPin() const
{
    return static_cast<gpio_num_t>(I2cDeviceDriver::GetSclPin());
}

void EspI2cDeviceDriver::Write(uint8_t deviceAddress, const uint8_t* data, size_t length)
{
    Assert::IsTrue(IsInitialized());

    Assert::Equals(i2c_master_write_to_device(GetPort(), deviceAddress, data, length, 1000 / portTICK_PERIOD_MS), 
        ESP_OK, "Failed to write to device");
}

void EspI2cDeviceDriver::Read(uint8_t deviceAddress, uint8_t* data, size_t length)
{
    Assert::IsTrue(IsInitialized());

    Assert::Equals(i2c_master_read_from_device(GetPort(), deviceAddress, data, length, 1000 / portTICK_PERIOD_MS), 
        ESP_OK, "Failed to read from device");
}

uint8_t EspI2cDeviceDriver::ReadRegister(uint8_t deviceAddress, uint8_t registerAddress)
{
    Assert::IsTrue(IsInitialized());

    uint8_t value = 0;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    Assert::IsNotNull(cmd, "cmd");

    // Write register address
    Assert::Equals(i2c_master_start(cmd), ESP_OK, "Failed to execute i2c_master_start");
    Assert::Equals(i2c_master_write_byte(cmd, (deviceAddress << 1) | I2C_MASTER_WRITE, true), ESP_OK, 
        "Failed to write device address");
    Assert::Equals(i2c_master_write_byte(cmd, registerAddress, true), ESP_OK,  "Failed to write register address");

    // Read one byte
    Assert::Equals(i2c_master_start(cmd), ESP_OK, "Failed to execute i2c_master_start");
    Assert::Equals(i2c_master_write_byte(cmd, (deviceAddress << 1) | I2C_MASTER_READ, true), ESP_OK, 
        "Failed to write device address");
    Assert::Equals(i2c_master_read_byte(cmd, &value, I2C_MASTER_LAST_NACK), ESP_OK, "Failed to read value");
    Assert::Equals(i2c_master_stop(cmd), ESP_OK, "Failed to execute i2c_master_stop");

    Assert::Equals(i2c_master_cmd_begin(GetPort(), cmd, 10 / portTICK_PERIOD_MS), ESP_OK, 
        "Failed to execute i2c_master_cmd_begin");
    i2c_cmd_link_delete(cmd);

    return value;
}

void EspI2cDeviceDriver::ReadRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t* data, size_t length)
{
    Assert::IsTrue(IsInitialized());

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    Assert::IsNotNull(cmd, "cmd");

    // Write register address
    Assert::Equals(i2c_master_start(cmd), ESP_OK, "Failed to execute i2c_master_start");
    Assert::Equals(i2c_master_write_byte(cmd, (deviceAddress << 1) | I2C_MASTER_WRITE, true), ESP_OK, 
        "Failed to write device address");
    Assert::Equals(i2c_master_write_byte(cmd, registerAddress, true), ESP_OK,  "Failed to write register address");

    // Read data
    Assert::Equals(i2c_master_start(cmd), ESP_OK, "Failed to execute i2c_master_start");
    Assert::Equals(i2c_master_write_byte(cmd, (deviceAddress << 1) | I2C_MASTER_READ, true), ESP_OK, 
        "Failed to write device address");
    Assert::Equals(i2c_master_read(cmd, data, length, I2C_MASTER_LAST_NACK), ESP_OK, "Failed to read value");
    Assert::Equals(i2c_master_stop(cmd), ESP_OK, "Failed to execute i2c_master_stop");

    Assert::Equals(i2c_master_cmd_begin(GetPort(), cmd, 10 / portTICK_PERIOD_MS), ESP_OK, 
        "Failed to execute i2c_master_cmd_begin");
    i2c_cmd_link_delete(cmd);
}

void EspI2cDeviceDriver::WriteRegister(
    uint8_t deviceAddress, uint8_t registerAddress, uint8_t value)
{
    Assert::IsTrue(IsInitialized());

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    Assert::IsNotNull(cmd, "cmd");

    Assert::Equals(i2c_master_start(cmd), ESP_OK, "Failed to execute i2c_master_start");
    Assert::Equals(i2c_master_write_byte(cmd, (deviceAddress << 1) | I2C_MASTER_WRITE, true), ESP_OK, 
        "Failed to write device address");
    Assert::Equals(i2c_master_write_byte(cmd, registerAddress, true), ESP_OK,  "Failed to write register address");
    Assert::Equals(i2c_master_write_byte(cmd, value, true), ESP_OK, "Failed to write value");
    Assert::Equals(i2c_master_stop(cmd), ESP_OK, "Failed to execute i2c_master_stop");

    Assert::Equals(i2c_master_cmd_begin(GetPort(), cmd, 10 / portTICK_PERIOD_MS), ESP_OK, 
        "Failed to execute i2c_master_cmd_begin");
    i2c_cmd_link_delete(cmd);
}

void EspI2cDeviceDriver::WriteRegister(
    uint8_t deviceAddress, uint8_t registerAddress, const uint8_t* data, size_t length)
{
    Assert::IsTrue(IsInitialized());

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    Assert::Equals(i2c_master_start(cmd), ESP_OK, "Failed to execute i2c_master_start");
    Assert::Equals(i2c_master_write_byte(cmd, (deviceAddress << 1) | I2C_MASTER_WRITE, true), ESP_OK, 
        "Failed to write device address");
    Assert::Equals(i2c_master_write_byte(cmd, registerAddress, true), ESP_OK,  "Failed to write register address");
    Assert::Equals(i2c_master_write(cmd, data, length, true), ESP_OK, "Failed to execute i2c_master_write");
    Assert::Equals(i2c_master_stop(cmd), ESP_OK, "Failed to execute i2c_master_stop");
    Assert::Equals(i2c_master_cmd_begin(GetPort(), cmd, 50 / portTICK_PERIOD_MS), ESP_OK, 
        "Failed to execute i2c_master_cmd_begin");
    i2c_cmd_link_delete(cmd);
}

#endif // ESP_PLATFORM
