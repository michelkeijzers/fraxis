#pragma once

#include "IDeviceModel.hpp"

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

class DeviceModel : public IDeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    explicit DeviceModel(
        M90::Assert::IAssert& assert,
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

    M90::Assert::IAssert &GetAssert() const;

    M90::String::IStringUtilities& GetStringUtilities() const;

  private:
    M90::Assert::IAssert &_assert;

    M90::String::IStringUtilities& _stringUtilities;
};
