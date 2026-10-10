#pragma once

#include "../../DomainModel.hpp"
#include "../../../M30_Messages/Types.hpp"
#include <cstdint>
#include <vector>

class MicrophoneDeviceModel;

class Inmp1441 : public DomainModel
{
public:
    static constexpr uint32_t SAMPLE_RATE = 16000;
    static constexpr uint16_t BITS_PER_SAMPLE = 16;
    static constexpr uint8_t CHANNELS = 1;
    static constexpr uint32_t BUFFER_SIZE = 1024;

    Inmp1441();
    ~Inmp1441() = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

    void StartRecording();
    void StopRecording();

    bool IsRecording() const;

    void ReadSamples(
        int16_t* buffer,
        size_t length);

    MicrophoneDeviceModel& GetMicrophoneDeviceModel();

private:
    MicrophoneDeviceModel* _microphoneDeviceModel;
    bool _isRecording;
};
