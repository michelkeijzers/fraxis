// @file Tm1637DeviceDriverTests.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "gtest/gtest.h"
#include "../../../../../main/M60_DeviceDrivers/I2c/Tm1637/Tm1637DeviceDriver.hpp"
#include "../../../../../main/M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../../../../main/M80_Services/Gpio/Gpio.hpp"

namespace
{
    class MockGpio : public M80::Gpio::Gpio
    {
    public:
        MockGpio() = default;
        esp_err_t ConfigAsOutput(uint8_t pin) override { return ESP_OK; }
        esp_err_t ConfigAsInterruptInput(uint8_t pin) override { return ESP_OK; }
        esp_err_t SetLevel(uint8_t pin, bool level) override { return ESP_OK; }
        esp_err_t AddInterruptHandler(int pin, void (*fn)(void*), void* arg) override { return ESP_OK; }
        void DelayUs(uint32_t us) override {}
    protected:
        esp_err_t InstallIsrServiceWhenNotInstalledYet() override { return ESP_OK; }
    };

    class MockTm1637DeviceModel : public Tm1637DeviceModel
    {
    public:
        MockTm1637DeviceModel() = default;
        ~MockTm1637DeviceModel() override = default;
        void Initialize() override {}
    };
}

namespace M60::Tm1637::Tests
{
    class Tm1637DeviceDriverTest : public ::testing::Test
    {
    protected:
        M60::I2c::Tm1637DeviceDriver     _driver;
        MockGpio                         _mockGpio;
        MockTm1637DeviceModel            _deviceModel;

        void SetUp() override
        {
            _driver.SetGpio(_mockGpio);
            _driver.SetDeviceModel(_deviceModel);
            _driver.SetPinsConfiguration(4, 5);
        }
    };

    TEST_F(Tm1637DeviceDriverTest, ConstructionAndSetupSucceeds)
    {
        SUCCEED();
    }
}