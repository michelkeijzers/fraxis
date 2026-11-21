// @file DeviceDriver.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only
 
#include "DeviceDriver.hpp"
#include "../M90_Utilities/Assert/IAssert.hpp"

namespace M60
{
    DeviceDriver::DeviceDriver(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities)
    : 
        _deviceModel(nullptr),
        _assert(assert),
        _stringUtilities(stringUtilities)
    {
        // No actions required.
    }

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    DeviceDriver::~DeviceDriver() = default;

    void DeviceDriver::SetDeviceModel(
        IDeviceModel& deviceModel)
    {
        _deviceModel = &deviceModel;
    }

    IDeviceModel& DeviceDriver::GetDeviceModel() const
    {
        return *_deviceModel;
    }

    M90::Assert::IAssert& DeviceDriver::GetAssert() const
    {
        return _assert;
    }

    M90::String::IStringUtilities& DeviceDriver::GetStringUtilities() const
    {
        return _stringUtilities;
    }
}
