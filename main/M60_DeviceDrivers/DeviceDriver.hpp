#pragma once

#include "IDeviceDriver.hpp"

namespace M60
{
    class DeviceDriver : public IDeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        DeviceDriver();

        DeviceDriver(const DeviceDriver&) = delete;
        DeviceDriver& operator=(const DeviceDriver&) = delete;
        DeviceDriver(DeviceDriver&&) = delete;
        DeviceDriver& operator=(DeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~DeviceDriver() override;

        void SetDeviceModel(
            IDeviceModel& deviceModel) override;
        [[nodiscard]] IDeviceModel& GetDeviceModel() const override;

    private:
        IDeviceModel* _deviceModel;
    };
}
