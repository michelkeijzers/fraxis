#pragma once

#include "../../../M60_DeviceDrivers/Audio/Inmp1441/Inmp1441DeviceDriver.hpp"
#include "../../DeviceModel.hpp"
#include <cstdint>

class Inmp1441DeviceModel : public DeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Inmp1441DeviceModel(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities);

    Inmp1441DeviceModel(
        const Inmp1441DeviceModel&) = delete;
    
    Inmp1441DeviceModel& operator=(
        const Inmp1441DeviceModel&) = delete;
    
    Inmp1441DeviceModel(
        Inmp1441DeviceModel&&) = delete;
    
    Inmp1441DeviceModel& operator=(
        Inmp1441DeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~Inmp1441DeviceModel() override;

    void Initialize() override;

    [[nodiscard]] uint8_t GetI2sPort() const;
    
    void SetI2sPort(
        uint8_t port);

    [[nodiscard]] bool IsRecording() const;
    
    void SetRecording(
        bool recording);

private:
    uint8_t _i2sPort;
    
    bool _isRecording;
};
