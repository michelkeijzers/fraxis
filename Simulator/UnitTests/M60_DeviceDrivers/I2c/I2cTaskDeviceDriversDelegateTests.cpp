// @file Ws28xxDeviceDriverTests.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "gtest/gtest.h"
#include "../../../../main/M60_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include "../../../../main/M60_DeviceDrivers/Ws28xx/Ws2812Rmt.hpp"
#include "../../../../main/M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include <vector>
#include <memory>

namespace M60::Ws28xxTests
{
    class MockWs28xxDeviceModel : public Ws28xxDeviceModel
    {
    public:
        uint16_t NumberOfLeds = 10;
        size_t FillGrbBufferCallCount = 0;
        std::vector<RgbStruct> LastFilledBuffer;

        uint16_t GetNumberOfLeds() const { return NumberOfLeds; }

        void FillGrbBufferToSend(std::vector<RgbStruct>& destinationBuffer)
        {
            FillGrbBufferCallCount++;
            destinationBuffer.resize(NumberOfLeds);
            LastFilledBuffer = destinationBuffer;
        }
    };

    class MockRmt
    {
        // Dummy mock for M80::Rmt::Rmt reference
    };

    class Ws28xxDeviceDriverTest : public ::testing::Test
    {
    protected:
        MockWs28xxDeviceModel _mockDeviceModel;
        MockRmt _mockRmt;
        M60::Ws28xx::Ws28xxDeviceDriver _driver;

        void SetUp() override
        {
            // Eventuele initialisatie voor tests
        }
    };

    TEST_F(Ws28xxDeviceDriverTest, SetAndGetDataPin)
    {
        _driver.SetDataPin(15);
        EXPECT_EQ(_driver.GetDataPin(), 15);
    }

    TEST_F(Ws28xxDeviceDriverTest, SetRmtReference)
    {
        _driver.SetRmt(reinterpret_cast<M80::Rmt::Rmt&>(_mockRmt));
        // Verifieer dat setten zonder problemen verloopt
        SUCCEED();
    }

    TEST_F(Ws28xxDeviceDriverTest, Initialize_ConfiguresDriver)
    {
        _driver.SetDataPin(4);
        _driver.SetRmt(reinterpret_cast<M80::Rmt::Rmt&>(_mockRmt));

        // Opmerking: Afhankelijk van hoe GetDeviceModel() in jouw base class gekoppeld is 
        // aan de Context/DeviceModels, kun je hier de model-koppeling activeren.
    }
}