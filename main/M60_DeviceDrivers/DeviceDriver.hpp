#pragma once

#include "IDeviceDriver.hpp"

namespace M60
{
    class DeviceDriver : public IDeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        DeviceDriver(
            M90::Assert::IAssert& assert);

        DeviceDriver(
            const DeviceDriver&) = delete;
        
        DeviceDriver& operator=(
            const DeviceDriver&) = delete;
        
        DeviceDriver(
            DeviceDriver&&) = delete;
        
        DeviceDriver& operator=(
            DeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~DeviceDriver() override;

        void SetDeviceModel(
            IDeviceModel& deviceModel) override;

        [[nodiscard]] IDeviceModel& GetDeviceModel() const override;

    protected:
        [[nodiscard]] M90::Assert::IAssert& GetAssert() const override;

    private:
        IDeviceModel* _deviceModel;

        M90::Assert::IAssert& _assert;
    };
}
