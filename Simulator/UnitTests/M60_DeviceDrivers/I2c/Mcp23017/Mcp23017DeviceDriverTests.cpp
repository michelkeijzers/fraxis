// @file I2cDeviceDriverTests.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "gtest/gtest.h"
#include "../../../../../main/M60_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../../../../../main/M80_Services/I2c/I2c.hpp"
#include "../../../../../main/M50_DeviceModels/IDeviceModel.hpp"
#include <vector>
#include <map>

namespace
{
    // Safe heap-allocated mock command structure to prevent pointer dereference crashes
    struct MockCmdLink
    {
        uint8_t deviceAddress = 0;
        uint8_t registerAddress = 0;
        std::vector<uint8_t> bytes;
    };

    class MockI2c : public M80::I2c::I2c
    {
    public:
        MockI2c() = default;

        bool IsValidPort(uint8_t /*port*/) override
        {
            IsValidPortCallCount++;
            return true;
        }

        esp_err_t ParamConfig(uint8_t port, uint8_t sdaPin, uint8_t sclPin, uint32_t frequency) override
        {
            ConfiguredPort = port;
            SdaPin = sdaPin;
            SclPin = sclPin;
            Frequency = frequency;
            ParamConfigCallCount++;
            return ESP_OK;
        }

        esp_err_t DriverInstall(uint8_t port) override
        {
            InstalledPort = port;
            DriverInstallCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterWriteToDevice(uint8_t port, uint8_t deviceAddress, const uint8_t* data, size_t length, uint32_t timeoutInMs) override
        {
            LastPort = port;
            LastDeviceAddress = deviceAddress;
            LastWrittenData.assign(data, data + length);
            TimeoutMs = timeoutInMs;
            MasterWriteToDeviceCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterReadFromDevice(uint8_t port, uint8_t deviceAddress, uint8_t* data, size_t length, uint32_t timeoutInMs) override
        {
            LastPort = port;
            LastDeviceAddress = deviceAddress;
            TimeoutMs = timeoutInMs;
            if (data != nullptr && length > 0)
            {
                data[0] = MockReadReturnValue;
            }
            MasterReadFromDeviceCallCount++;
            return ESP_OK;
        }

        void* CmdLinkCreate() override
        {
            CmdLinkCreateCallCount++;
            return new MockCmdLink(); // Return a valid heap-allocated object
        }

        void CmdLinkDelete(void* cmd) override
        {
            CmdLinkDeleteCallCount++;
            delete static_cast<MockCmdLink*>(cmd); // Clean up safely
        }

        esp_err_t MasterStart(void* /*cmd*/) override
        {
            MasterStartCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterWriteDeviceAddress(void* cmd, uint8_t deviceAddress) override
        {
            auto* link = static_cast<MockCmdLink*>(cmd);
            if (link != nullptr)
            {
                link->deviceAddress = deviceAddress;
                LastDeviceAddress = deviceAddress;
            }
            MasterWriteDeviceAddressCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterWriteRegisterAddress(void* cmd, uint8_t registerAddress) override
        {
            auto* link = static_cast<MockCmdLink*>(cmd);
            if (link != nullptr)
            {
                link->registerAddress = registerAddress;
                LastRegisterAddress = registerAddress;
            }
            MasterWriteRegisterAddressCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterWriteByte(void* cmd, uint8_t byteToWrite) override
        {
            auto* link = static_cast<MockCmdLink*>(cmd);
            if (link != nullptr)
            {
                link->bytes.push_back(byteToWrite);
                LastWrittenBytes.push_back(byteToWrite);
            }
            MasterWriteByteCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterReadByte(void* /*cmd*/, uint8_t* byteToRead) override
        {
            if (byteToRead != nullptr)
            {
                *byteToRead = MockReadReturnValue;
            }
            MasterReadByteCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterWrite(void* cmd, const uint8_t* data, size_t length) override
        {
            auto* link = static_cast<MockCmdLink*>(cmd);
            if (link != nullptr && data != nullptr)
            {
                link->bytes.insert(link->bytes.end(), data, data + length);
                LastWrittenData.assign(data, data + length);
            }
            MasterWriteCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterRead(void* /*cmd*/, uint8_t* data, size_t length) override
        {
            if (data != nullptr && length > 0)
            {
                data[0] = MockReadReturnValue;
            }
            MasterReadCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterStop(void* /*cmd*/) override
        {
            MasterStopCallCount++;
            return ESP_OK;
        }

        esp_err_t MasterCmdBegin(uint8_t port, void* /*cmd*/, uint32_t timeoutInMs) override
        {
            LastPort = port;
            TimeoutMs = timeoutInMs;
            MasterCmdBeginCallCount++;
            return ESP_OK;
        }

        // Tracking fields
        uint8_t ConfiguredPort = 0;
        uint8_t InstalledPort = 0;
        uint8_t SdaPin = 0;
        uint8_t SclPin = 0;
        uint32_t Frequency = 0;
        uint8_t LastPort = 0;
        uint8_t LastDeviceAddress = 0;
        uint8_t LastRegisterAddress = 0;
        uint32_t TimeoutMs = 0;
        std::vector<uint8_t> LastWrittenData;
        std::vector<uint8_t> LastWrittenBytes;
        uint8_t MockReadReturnValue = 0xAA;

        size_t IsValidPortCallCount = 0;
        size_t ParamConfigCallCount = 0;
        size_t DriverInstallCallCount = 0;
        size_t MasterWriteToDeviceCallCount = 0;
        size_t MasterReadFromDeviceCallCount = 0;
        size_t CmdLinkCreateCallCount = 0;
        size_t CmdLinkDeleteCallCount = 0;
        size_t MasterStartCallCount = 0;
        size_t MasterWriteDeviceAddressCallCount = 0;
        size_t MasterWriteRegisterAddressCallCount = 0;
        size_t MasterWriteByteCallCount = 0;
        size_t MasterReadByteCallCount = 0;
        size_t MasterWriteCallCount = 0;
        size_t MasterReadCallCount = 0;
        size_t MasterStopCallCount = 0;
        size_t MasterCmdBeginCallCount = 0;
    };

    class MockDeviceModel : public IDeviceModel
    {
    public:
        ~MockDeviceModel() override = default;
        void Initialize() override {}
    };
}

namespace M60::I2c::Tests
{
    class I2cDeviceDriverTest : public ::testing::Test
    {
    protected:
        I2cDeviceDriver _driver;
        MockI2c         _mockI2c;
        MockDeviceModel _deviceModel;

        void SetUp() override
        {
            _driver.SetI2c(_mockI2c);
            _driver.SetDeviceModel(_deviceModel);

            // Set required configuration so initialization succeeds
            _driver.SetConfiguration(0, 21, 22, 100000);

            // Mark the driver as initialized to satisfy assertion checks
            _driver.Initialize();
        }
    };

    TEST_F(I2cDeviceDriverTest, SetAndGetI2c_ReturnsCorrectReference)
    {
        EXPECT_EQ(&_driver.GetI2c(), &_mockI2c);
    }

    TEST_F(I2cDeviceDriverTest, SetConfiguration_StoresParameters)
    {
        _driver.SetConfiguration(1, 21, 22, 100000);
        SUCCEED();
    }

    TEST_F(I2cDeviceDriverTest, Write_DelegatesToI2cLayer)
    {
        uint8_t testData[] = { 0x01, 0x02, 0x03 };

        _driver.Write(0x27, testData, sizeof(testData));

        EXPECT_EQ(_mockI2c.LastDeviceAddress, 0x27);
        EXPECT_EQ(_mockI2c.MasterWriteToDeviceCallCount, 1U);
        EXPECT_EQ(_mockI2c.LastWrittenData.size(), 3U);
        EXPECT_EQ(_mockI2c.LastWrittenData[0], 0x01);
    }

    TEST_F(I2cDeviceDriverTest, ReadRegister_ReturnsExpectedByte)
    {
        uint8_t result = _driver.ReadRegister(0x20, 0x12);

        EXPECT_EQ(_mockI2c.LastDeviceAddress, 0x20);
        EXPECT_EQ(_mockI2c.LastRegisterAddress, 0x12);
        EXPECT_EQ(result, 0xAA);
    }

    TEST_F(I2cDeviceDriverTest, WriteRegister_ByteOverload_SendsCorrectBuffer)
    {
        _driver.WriteRegister(0x20, 0x0A, 0xFF);

        EXPECT_EQ(_mockI2c.LastDeviceAddress, 0x20);
        EXPECT_EQ(_mockI2c.LastRegisterAddress, 0x0A);
        ASSERT_GE(_mockI2c.LastWrittenBytes.size(), 1U);
        EXPECT_EQ(_mockI2c.LastWrittenBytes[0], 0xFF);
    }
}