// @file DeviceDriver.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IDeviceDriver.hpp"

namespace M90
{
    namespace Assert
    {
        class IAssert;
    }

    namespace String
    {
        class StringUtilities;
    }
}

namespace M60
{
    class DeviceDriver : public IDeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        DeviceDriver(
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

        DeviceDriver(
            const DeviceDriver&) = delete;
        
        DeviceDriver& operator=(
            const DeviceDriver&) = delete;
        
        DeviceDriver(
            DeviceDriver&&) = delete;
        
        DeviceDriver& operator=(
            DeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        virtual ~DeviceDriver() override;

        void SetDeviceModel(
            IDeviceModel& deviceModel) override;

        [[nodiscard]] IDeviceModel& GetDeviceModel() const override;

    protected:
        [[nodiscard]] M90::Assert::IAssert& GetAssert() const override;

        [[nodiscard]] M90::String::IStringUtilities& GetStringUtilities() const override;

    private:
        IDeviceModel* _deviceModel;

        M90::Assert::IAssert& _assert;

        M90::String::IStringUtilities& _stringUtilities;
    };
}
