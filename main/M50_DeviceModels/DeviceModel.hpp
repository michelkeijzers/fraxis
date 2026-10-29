#pragma once

#include "IDeviceModel.hpp"

class DeviceModel : public IDeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    DeviceModel();

    DeviceModel(const DeviceModel&) = delete;
    DeviceModel& operator=(const DeviceModel&) = delete;
    DeviceModel(DeviceModel&&) = delete;
    DeviceModel& operator=(DeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~DeviceModel() override;
};
