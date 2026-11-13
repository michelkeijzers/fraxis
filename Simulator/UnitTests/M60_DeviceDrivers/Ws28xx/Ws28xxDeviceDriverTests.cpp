// @file Ws28xxDeviceDriverTests.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "gtest/gtest.h"
#include "../../../../main/M60_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include "../../../../main/M60_DeviceDrivers/Ws28xx/Ws2812Rmt.hpp"
#include "../../../../main/M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../../../../main/M80_Services/Rmt/Rmt.hpp"
#include <vector>
#include <memory>

namespace
{
    class MockRmt : public M80::Rmt::Rmt
    {
    public:
        MockRmt() = default;
        ~MockRmt() override = default;

        esp_err_t DelEncoder() override { return ESP_OK; }
        esp_err_t DelChannel() override { return ESP_OK; }
        esp_err_t NewTxChannel(uint8_t /*pin*/) override { return ESP_OK; }
        esp_err_t Enable() override { return ESP_OK; }
        esp_err_t NewSimpleEncoder() override { return ESP_OK; }
        esp_err_t Transmit(const void* /*payload*/, size_t /*payload_bytes*/) override { return ESP_OK; }
        esp_err_t TxWaitAllDone() override { return ESP_OK; }
    };

    class MockWs28xxDeviceModel : public Ws28xxDeviceModel
    {
    public:
        size_t FillGrbBufferCallCount = 0;
        std::vector<RgbStruct> LastDestinationBuffer;
                
        MockWs28xxDeviceModel()
        {
            std::cout << "MockWs28xxDeviceModel ctor\n";
        }

        ~MockWs28xxDeviceModel() override
        {
            std::cout << "MockWs28xxDeviceModel dtor\n";
        }

        void FillGrbBufferToSend(
            std::vector<RgbStruct>& destinationBuffer) override
        {
            FillGrbBufferCallCount++;

            for (auto& led : destinationBuffer)
            {
                led.red = 1;
                led.green = 2;
                led.blue = 3;
            }

            LastDestinationBuffer = destinationBuffer;
        }
    };
}

namespace M60::Ws28xxTests
{
    class Ws28xxDeviceDriverTest : public ::testing::Test
    {
    protected:
        MockRmt                         _mockRmt;
        MockWs28xxDeviceModel           _deviceModel;
        M60::Ws28xx::Ws28xxDeviceDriver _driver;

        void SetUp() override
        {
            std::cout << "1\n";
            _driver.SetDataPin(4);

            std::cout << "2\n";
            _driver.SetRmt(_mockRmt);

            std::cout << "3\n";
            _driver.SetDeviceModel(_deviceModel);

            std::cout << "4\n";
            _deviceModel.SetNumberOfLeds(10);

            std::cout << "5\n";
        }
    };

    TEST_F(Ws28xxDeviceDriverTest, DISABLED_Ws28xxSetAndGetDataPin)
    {
        // Test puur de getter en setter zonder afhankelijkheden van RMT of DeviceModel
        M60::Ws28xx::Ws28xxDeviceDriver localDriver;
        localDriver.SetDataPin(15);
        EXPECT_EQ(localDriver.GetDataPin(), 15);
    }

    TEST_F(Ws28xxDeviceDriverTest, InitializeAndSetupSucceeds)
    {
        _driver.Initialize();

        auto* p = new int(123);
        delete p;
        //EXPECT_EQ(_driver.GetDataPin(), 4);
        //SUCCEED();
    }

    TEST_F(Ws28xxDeviceDriverTest, DISABLED_WriteToLedStripFillsAndSendsBuffer)
    {
        _driver.Initialize();
        _driver.WriteToLedStrip();

        EXPECT_EQ(_deviceModel.FillGrbBufferCallCount, 1U);
        EXPECT_EQ(_deviceModel.LastDestinationBuffer.size(), 10U);
    }

    TEST(Ws28xxDeviceDriverStandaloneTest, SimpleSetAndGetDataPin)
    {
        M60::Ws28xx::Ws28xxDeviceDriver localDriver;
        localDriver.SetDataPin(15);
        EXPECT_EQ(localDriver.GetDataPin(), 15);
    }
}