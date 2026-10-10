#pragma once

#include "../../M60_DeviceDrivers/Audio/Dac/Max53987aDeviceDriver.hpp"
#include "../DeviceModel.hpp"
#include <cstdint>

class DacDeviceModel : public DeviceModel
{
public:
    DacDeviceModel();
    ~DacDeviceModel() = default;

    void Initialize() override;

    uint8_t GetI2sPort() const;
    void SetI2sPort(
        uint8_t port);

private:
    uint8_t _i2sPort;
};
