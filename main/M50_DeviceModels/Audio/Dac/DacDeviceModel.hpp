#pragma once

#include "../../../M60_DeviceDrivers/Audio/Dac/Max53987aDeviceDriver.hpp"
#include "../../DeviceModel.hpp"
#include <cstdint>

class DacDeviceModel : public DeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    DacDeviceModel();

    DacDeviceModel(const DacDeviceModel&) = delete;
    DacDeviceModel& operator=(const DacDeviceModel&) = delete;
    DacDeviceModel(DacDeviceModel&&) = delete;
    DacDeviceModel& operator=(DacDeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~DacDeviceModel() override;

    void Initialize() override;

    [[nodiscard]] uint8_t GetI2sPort() const;
    void SetI2sPort(
        uint8_t port);

private:
    uint8_t _i2sPort;
};
