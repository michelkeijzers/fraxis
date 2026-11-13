// @file Lcd2004DeviceDriverTests.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "gtest/gtest.h"
#include "../../../../../main/M60_DeviceDrivers/DeviceDriver.hpp"
#include "../../../../../main/M50_DeviceModels/IDeviceModel.hpp"

namespace M60::Lcd2004Tests
{
    // Minimal mock implementation of IDeviceModel for dependency injection testing
    class MockDeviceModel : public IDeviceModel
    {
    public:
        ~MockDeviceModel() override = default;

        // Satisfy pure virtual Initialize() inherited from IDeviceModel's base interface
        void Initialize() override
        {
            // Stub implementation for testing purposes
        }
    };

    // Concrete testable derived class to instantiate the abstract DeviceDriver base
    class TestableDeviceDriver : public M60::DeviceDriver
    {
    public:
        void Initialize() override
        {
            // Stub implementation for testing purposes
        }
    };

    // Unique fixture name to prevent collisions with DeviceDriverTests.cpp
    class Lcd2004DeviceDriverTest : public ::testing::Test
    {
    protected:
        TestableDeviceDriver _driver;
        MockDeviceModel      _deviceModel;
    };

    TEST_F(Lcd2004DeviceDriverTest, SetAndGetDeviceModel_ReturnsCorrectReference)
    {
        // Act
        _driver.SetDeviceModel(_deviceModel);

        // Assert
        IDeviceModel& retrievedModel = _driver.GetDeviceModel();
        EXPECT_EQ(&retrievedModel, &_deviceModel);
    }
}