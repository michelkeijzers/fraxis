// @file TestDeviceDriver.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "gtest/gtest.h"
#include "../../../main/M60_DeviceDrivers/DeviceDriver.hpp"
#include "../../../main/M50_DeviceModels/IDeviceModel.hpp"

namespace M60::Tests
{
    // Minimal mock implementation of IDeviceModel for dependency injection testing
    class MockDeviceModel : public IDeviceModel
    {
    public:
        ~MockDeviceModel() override = default;

        // Satisfy pure virtual Initialize() (or equivalent) inherited from IDeviceModel's base interface
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
}

namespace M60::Tests
{
    class DeviceDriverTest : public ::testing::Test
    {
    protected:
        TestableDeviceDriver _driver;
        MockDeviceModel      _deviceModel;
    };

    TEST_F(DeviceDriverTest, SetAndGetDeviceModel_ReturnsCorrectReference)
    {
        // Act
        _driver.SetDeviceModel(_deviceModel);

        // Assert
        IDeviceModel& retrievedModel = _driver.GetDeviceModel();
        EXPECT_EQ(&retrievedModel, &_deviceModel);
    }
}