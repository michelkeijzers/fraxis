#pragma once

#include "../AudioDeviceDriver.hpp"
#include <cstdint>

class Inmp1441DeviceDriver : public AudioDeviceDriver
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Inmp1441DeviceDriver();

    Inmp1441DeviceDriver(const Inmp1441DeviceDriver&) = delete;
    Inmp1441DeviceDriver& operator=(const Inmp1441DeviceDriver&) = delete;
    Inmp1441DeviceDriver(Inmp1441DeviceDriver&&) = delete;
    Inmp1441DeviceDriver& operator=(Inmp1441DeviceDriver&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~Inmp1441DeviceDriver() override;

    void StartRecording();
    void StopRecording();

    size_t ReadSamples(
        int16_t* buffer,
        size_t length);

private:
    bool _isRecording;
};
