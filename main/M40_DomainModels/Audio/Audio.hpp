#pragma once

#include "../DomainModel.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <vector>

class AudioDeviceModel;

class Audio : public DomainModel
{
public:
    static constexpr uint32_t SAMPLE_RATE = 16000;
    static constexpr uint16_t BITS_PER_SAMPLE = 16;
    static constexpr uint8_t CHANNELS = 1;
    static constexpr uint32_t BUFFER_SIZE = 1024;

    Audio();
    ~Audio() = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

    AudioDeviceModel& GetAudioDeviceModel();

private:
    AudioDeviceModel* _audioDeviceModel;
};
