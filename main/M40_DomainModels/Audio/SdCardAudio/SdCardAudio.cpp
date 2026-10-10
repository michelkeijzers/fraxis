#include "SdCardAudio.hpp"
#include "../../../M50_DeviceModels/Spi/MicroSdCard/MicroSdCardDeviceModel.hpp"

SdCardAudio::SdCardAudio()
: _microSdCard(nullptr)
{
}

void SdCardAudio::SetMicroSdCard(
    MicroSdCard& microSdCard)
{
    _microSdCard = &microSdCard;
}

bool SdCardAudio::LoadSample(
    uint8_t sampleId,
    const std::string& filename)
{
    if (sampleId >= MAX_SAMPLES)
    {
        return false;
    }

    return false;
}

bool SdCardAudio::SaveSample(
    uint8_t sampleId,
    const std::string& filename,
    const int16_t* data,
    size_t length)
{
    if (sampleId >= MAX_SAMPLES)
    {
        return false;
    }

    return false;
}

const int16_t* SdCardAudio::GetSample(
    uint8_t sampleId) const
{
    if (sampleId >= MAX_SAMPLES)
    {
        return nullptr;
    }
    return _samples[sampleId].data();
}

size_t SdCardAudio::GetSampleLength(
    uint8_t sampleId) const
{
    if (sampleId >= MAX_SAMPLES)
    {
        return 0;
    }
    return _samples[sampleId].size();
}

bool SdCardAudio::PlaySample(
    uint8_t sampleId)
{
    return false;
}

bool SdCardAudio::StreamMusic(
    const std::string& filename)
{
    return false;
}
