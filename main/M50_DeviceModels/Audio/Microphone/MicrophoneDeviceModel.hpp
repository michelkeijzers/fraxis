#pragma once

#include "../../../M60_DeviceDrivers/Audio/Microphone/Inmp1441DeviceDriver.hpp"
#include "../../DeviceModel.hpp"
#include <cstdint>

class MicrophoneDeviceModel : public DeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    MicrophoneDeviceModel();

    MicrophoneDeviceModel(const MicrophoneDeviceModel&) = delete;
    MicrophoneDeviceModel& operator=(const MicrophoneDeviceModel&) = delete;
    MicrophoneDeviceModel(MicrophoneDeviceModel&&) = delete;
    MicrophoneDeviceModel& operator=(MicrophoneDeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~MicrophoneDeviceModel() override;

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
