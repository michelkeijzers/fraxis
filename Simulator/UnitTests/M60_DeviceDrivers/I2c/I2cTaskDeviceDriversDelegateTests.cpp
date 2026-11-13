// @file I2cTaskDeviceDriversDelegateTests.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "gtest/gtest.h"
#include "../../../../main/M10_Composition/Context/Context.hpp"
#include "../../../../main/M60_DeviceDrivers/I2c/I2cTaskDeviceDriversDelegate.hpp"
#include "../../../../main/M90_Utilities/Time/TimeUtilities.hpp"

namespace M60::I2cTests
{
    class MockLcd2004DeviceDriver : public M60::Lcd2004::Lcd2004DeviceDriver
    {
    public:
        MockLcd2004DeviceDriver() = default;
        // Override methods as needed for verification or stubbing
    };

    class I2cTaskDeviceDriversDelegateTest : public ::testing::Test
    {
    protected:
        Context _context;
        M60::I2c::I2cTaskDeviceDriversDelegate _delegate{ _context };

        void SetUp() override
        {
            DeviceDriversContext& deviceDriversContext = _context.GetDeviceDrivers();

            // Inject the mock Lcd2004 device driver
            deviceDriversContext.SetLcd2004DeviceDriver(std::make_unique<MockLcd2004DeviceDriver>());

            deviceDriversContext.GetLcd2004DeviceDriver().Initialize();
            deviceDriversContext.GetMcp23017DeviceDriver().Initialize();

            for (uint8_t i = 0; i < 3; ++i)
            {
                _context.GetDeviceDrivers().GetTm1637DeviceDriverId(static_cast<Types::ETm1637Id>(i)).Initialize();
            }
        }
    };

    TEST_F(I2cTaskDeviceDriversDelegateTest, Initialize_Succeeds)
    {
        _delegate.Initialize();
        SUCCEED();
    }

    TEST_F(I2cTaskDeviceDriversDelegateTest, Run_ExecutesWithoutCrash)
    {
        _delegate.Initialize();
        _delegate.Run();
        SUCCEED();
    }
}