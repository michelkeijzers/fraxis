#pragma once

#include "../../M60_DeviceDrivers/Audio/Microphone/Inmp1441DeviceDriver.hpp"
#include "../DeviceModel.hpp"
#include <cstdint>

class MicrophoneDeviceModel : public DeviceModel
{
public:
    MicrophoneDeviceModel();
    ~MicrophoneDeviceModel() = default;

    void Initialize() override;

    uint8_t GetI2sPort() const;
    void SetI2sPort(
        uint8_t port);

    bool IsRecording() const;
    void SetRecording(
        bool recording);

private:
    uint8_t _i2sPort;
    bool _isRecording;
};
