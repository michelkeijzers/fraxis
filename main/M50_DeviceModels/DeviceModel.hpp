#pragma once

#include "IDeviceModel.hpp"

namespace M90
{
    namespace Assert
    {
        class IAssert;
    }

    namespace Log
    {
        class ILog;
    }

    namespace String
    {
        class IStringUtilities;
    }
}

namespace M50
{
    class DeviceModel : public IDeviceModel
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        explicit DeviceModel(
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log,
            M90::String::IStringUtilities& stringUtilities);

        DeviceModel(
            const DeviceModel&) = delete;

        DeviceModel& operator=(
            const DeviceModel&) = delete;

        DeviceModel(
            DeviceModel&&) = delete;

        DeviceModel& operator=(
            DeviceModel&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~DeviceModel() override = default;

        M90::Assert::IAssert& GetAssert() const;

        M90::Log::ILog& GetLog() const;

        M90::String::IStringUtilities& GetStringUtilities() const;

    private:
        M90::Assert::IAssert& _assert;

        M90::Log::ILog& _log;

        M90::String::IStringUtilities& _stringUtilities;
    };
}
