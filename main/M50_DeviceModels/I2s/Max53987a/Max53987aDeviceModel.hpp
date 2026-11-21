#pragma once

#include "../../../M60_DeviceDrivers/I2s/Max53987a/Max53987aDeviceDriver.hpp"
#include "../../DeviceModel.hpp"
#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

class Max53987aDeviceModel : public DeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Max53987aDeviceModel(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities);

    Max53987aDeviceModel(
        const Max53987aDeviceModel&) = delete;
    
    Max53987aDeviceModel& operator=(
        const Max53987aDeviceModel&) = delete;
    
    Max53987aDeviceModel(
        Max53987aDeviceModel&&) = delete;
    
    Max53987aDeviceModel& operator=(
        Max53987aDeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~Max53987aDeviceModel() override;

    void Initialize() override;

    [[nodiscard]] uint8_t GetI2sPort() const;
    
    void SetI2sPort(
        uint8_t port);

private:
    uint8_t _i2sPort;
};
