#pragma once

#include "../AudioDeviceDriver.hpp"
#include <cstdint>

class Inmp1441DeviceDriver : public AudioDeviceDriver
{
public:
    Inmp1441DeviceDriver();
    ~Inmp1441DeviceDriver() = default;

    void StartRecording();
    void StopRecording();

    size_t ReadSamples(
        int16_t* buffer,
        size_t length);

private:
    bool _isRecording;
};
