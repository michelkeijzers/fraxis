// @file IDeviceDriver.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../M90_Utilities/Initializable/Initializable.hpp"

namespace M90
{
    namespace Assert
    {
        class IAssert;
    }

    namespace String
    {
        class IStringUtilities;
    }
}

namespace M50
{
    class IDeviceModel;
}

namespace M60
{
    class IDeviceDriver : public M90::Initializable::Initializable
    {
    public:
        virtual ~IDeviceDriver() override = default;

        virtual void SetDeviceModel(
            M50::IDeviceModel& deviceModel) = 0;

        [[nodiscard]] virtual M50::IDeviceModel& GetDeviceModel() const = 0;

        [[nodiscard]] virtual M90::Assert::IAssert& GetAssert() const = 0;

        [[nodiscard]] virtual M90::String::IStringUtilities& GetStringUtilities() const = 0;
    };
}
