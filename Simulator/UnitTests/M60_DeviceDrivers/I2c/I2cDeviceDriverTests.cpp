// @file I2cDeviceDriverTests.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "gtest/gtest.h"
#include "../../../../main/M60_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../../../../main/M80_Services/I2c/I2c.hpp"

namespace
{
    class MockI2c : public M80::I2c::I2c
    {
    public:
        MockI2c() = default;

        bool IsValidPort(uint8_t port) override
        {
            IsValidPortCallCount++;
            return port == 0 || port == 1;
        }

        esp_err_t ParamConfig(uint8_t port, uint8_t sda_io_num, uint8_t scl_io_num, uint32_t clk_speed) override
        {
            ParamConfigCallCount++;
            LastPort = port;
            LastSda = sda_io_num;
            LastScl = scl_io_num;
            LastFrequency = clk_speed;
            return ParamConfigResult;
        }

        esp_err_t DriverInstall(uint8_t port) override
        {
            DriverInstallCallCount++;
            return DriverInstallResult;
        }

        esp_err_t MasterWriteToDevice(
            uint8_t i2c_num, uint8_t address, const uint8_t* data, size_t size, uint32_t ticks_to_wait) override
        {
            MasterWriteCallCount++;
            return MasterWriteResult;
        }

        esp_err_t MasterReadFromDevice(uint8_t i2c_num, uint8_t address, uint8_t* data, size_t size, uint32_t ticks_to_wait) override
        {
            MasterReadCallCount++;
            return MasterReadResult;
        }

        void* CmdLinkCreate() override
        {
            CmdLinkCreateCallCount++;
            return FakedCmdLink;
        }

        esp_err_t MasterStart(void* cmd_handle) override
        {
            MasterStartCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterWriteDeviceAddress(void* cmd_handle, uint8_t address) override
        {
            MasterWriteDeviceAddressCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterWriteRegisterAddress(void* cmd_handle, uint8_t reg_address) override
        {
            MasterWriteRegisterAddressCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterWriteByte(void* cmd_handle, uint8_t data) override
        {
            MasterWriteByteCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterWrite(void* cmd_handle, const uint8_t* data, size_t data_len) override
        {
            MasterWriteCmdCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterReadByte(void* cmd_handle, uint8_t* data) override
        {
            MasterReadByteCallCount++;
            if (data) {
                *data = 0x55;
            }
            return ESP_OK;
        }

        esp_err_t MasterRead(void* cmd_handle, uint8_t* data, size_t data_len) override
        {
            MasterReadCmdCallCount++;
            if (data && data_len > 0) {
                data[0] = 0xAA;
            }
            return ESP_OK;
        }

        esp_err_t MasterStop(void* cmd_handle) override
        {
            MasterStopCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterCmdBegin(uint8_t i2c_num, void* cmd_handle, uint32_t ticks_to_wait) override
        {
            MasterCmdBeginCallCount++;
            return MasterCmdBeginResult;
        }

        void CmdLinkDelete(void* cmd_handle) override
        {
            CmdLinkDeleteCallCount++;
        }

    public:
        size_t IsValidPortCallCount = 0;
        size_t ParamConfigCallCount = 0;
        size_t DriverInstallCallCount = 0;
        size_t MasterWriteCallCount = 0;
        size_t MasterReadCallCount = 0;
        size_t CmdLinkCreateCallCount = 0;
        size_t MasterStartCallCount = 0;
        size_t MasterWriteDeviceAddressCallCount = 0;
        size_t MasterWriteRegisterAddressCallCount = 0;
        size_t MasterWriteByteCallCount = 0;
        size_t MasterWriteCmdCallCount = 0;
        size_t MasterReadByteCallCount = 0;
        size_t MasterReadCmdCallCount = 0;
        size_t MasterStopCallCount = 0;
        size_t MasterCmdBeginCallCount = 0;
        size_t CmdLinkDeleteCallCount = 0;

        uint8_t LastPort = 0;
        uint8_t LastSda = 0;
        uint8_t LastScl = 0;
        uint32_t LastFrequency = 0;

        esp_err_t ParamConfigResult = ESP_OK;
        esp_err_t DriverInstallResult = ESP_OK;
        esp_err_t MasterWriteResult = ESP_OK;
        esp_err_t MasterReadResult = ESP_OK;
        esp_err_t MasterCmdBeginResult = ESP_OK;
        void* FakedCmdLink = reinterpret_cast<void*>(0x12345678);
    };

    class StandaloneI2cDeviceDriverTest : public ::testing::Test
    {
    protected:
        M60::I2c::I2cDeviceDriver _driver;
        MockI2c                   _mockI2c;

        void SetUp() override
        {
            _driver.SetI2c(_mockI2c);
        }
    };
}

namespace M60::I2cTests
{
    TEST_F(StandaloneI2cDeviceDriverTest, SetConfiguration_ValidatesParameters)
    {
        _driver.SetConfiguration(0, 21, 22, 100'000);
        SUCCEED();
    }

    TEST_F(StandaloneI2cDeviceDriverTest, Initialize_CallsParamConfigAndDriverInstall)
    {
        _driver.SetConfiguration(0, 21, 22, 400'000);
        _driver.Initialize();

        EXPECT_EQ(_mockI2c.ParamConfigCallCount, 1U);
        EXPECT_EQ(_mockI2c.DriverInstallCallCount, 1U);
        EXPECT_TRUE(_driver.IsInitialized());
    }

    TEST_F(StandaloneI2cDeviceDriverTest, Write_PerformsMasterWrite)
    {
        _driver.SetConfiguration(0, 21, 22, 100'000);
        _driver.Initialize();

        uint8_t data[] = { 0x01, 0x02 };
        _driver.Write(0x38, data, 2);

        EXPECT_EQ(_mockI2c.MasterWriteCallCount, 1U);
    }

    TEST_F(StandaloneI2cDeviceDriverTest, Read_PerformsMasterRead)
    {
        _driver.SetConfiguration(0, 21, 22, 100'000);
        _driver.Initialize();

        uint8_t data[2] = { 0 };
        _driver.Read(0x38, data, 2);

        EXPECT_EQ(_mockI2c.MasterReadCallCount, 1U);
    }

    TEST_F(StandaloneI2cDeviceDriverTest, ReadRegister_ReturnsExpectedByte)
    {
        _driver.SetConfiguration(0, 21, 22, 100'000);
        _driver.Initialize();

        uint8_t val = _driver.ReadRegister(0x38, 0x10);
        EXPECT_EQ(val, 0x55);
        EXPECT_EQ(_mockI2c.CmdLinkCreateCallCount, 1U);
        EXPECT_EQ(_mockI2c.CmdLinkDeleteCallCount, 1U);
    }

    TEST_F(StandaloneI2cDeviceDriverTest, ReadRegister_Buffer_Succeeds)
    {
        _driver.SetConfiguration(0, 21, 22, 100'000);
        _driver.Initialize();

        uint8_t buffer[2] = { 0 };
        _driver.ReadRegister(0x38, 0x10, buffer, 2);

        EXPECT_EQ(buffer[0], 0xAA);
        EXPECT_EQ(_mockI2c.MasterReadCmdCallCount, 1U);
        EXPECT_EQ(_mockI2c.CmdLinkDeleteCallCount, 1U);
    }

    TEST_F(StandaloneI2cDeviceDriverTest, WriteRegister_Byte_Succeeds)
    {
        _driver.SetConfiguration(0, 21, 22, 100'000);
        _driver.Initialize();

        _driver.WriteRegister(0x38, 0x10, 0xFF);
        EXPECT_EQ(_mockI2c.MasterWriteByteCallCount, 1U);
        EXPECT_EQ(_mockI2c.CmdLinkDeleteCallCount, 1U);
    }

    TEST_F(StandaloneI2cDeviceDriverTest, WriteRegister_Buffer_Succeeds)
    {
        _driver.SetConfiguration(0, 21, 22, 100'000);
        _driver.Initialize();

        uint8_t data[] = { 0x11, 0x22 };
        _driver.WriteRegister(0x38, 0x10, data, 2);

        EXPECT_EQ(_mockI2c.MasterWriteCmdCallCount, 1U);
        EXPECT_EQ(_mockI2c.CmdLinkDeleteCallCount, 1U);
    }
}