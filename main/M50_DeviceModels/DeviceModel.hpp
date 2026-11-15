#pragma once

#include "IDeviceModel.hpp"

class DeviceModel : public IDeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    explicit DeviceModel(
        M90::Assert::IAssert& assert);

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

    M90::Assert::IAssert &GetAssert() const override;

  private:
    M90::Assert::IAssert &_assert;
};
