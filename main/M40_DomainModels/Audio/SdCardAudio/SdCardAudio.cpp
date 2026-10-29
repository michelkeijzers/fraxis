#include "SdCardAudio.hpp"
#include "../../../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"

SdCardAudio::SdCardAudio()
: _microSdCard(nullptr)
{
}


void SdCardAudio::SetMicroSdCard(
    MicroSdCard& microSdCard)
{
    _microSdCard = &microSdCard;
}

bool SdCardAudio::LoadSample( // NOSONAR S5817: const
    uint8_t sampleId,
    const std::string& /* filename */)
{
    // NOSONAR TODO SD
    if (sampleId >= MAX_SAMPLES)
    {
        return true;
    }

    return false;
}

bool SdCardAudio::SaveSample( // NOSONAR S5817: const
    uint8_t sampleId,
    const std::string& /* filename */,
    const int16_t* /* data */,
    size_t /* length */)
{
    // NOSONAR TODO SD
    if (sampleId >= MAX_SAMPLES)
    {
        return true;
    }

    return false;
}

const int16_t* SdCardAudio::GetSample(
    uint8_t sampleId) const
{
    // NOSONAR TODO SD
    if (sampleId >= MAX_SAMPLES)
    {
        return nullptr;
    }
    return _samples[sampleId].data();
}

size_t SdCardAudio::GetSampleLength(
    uint8_t sampleId) const
{
    // NOSONAR TODO SD
    if (sampleId >= MAX_SAMPLES)
    {
        return 0;
    }
    return _samples[sampleId].size();
}

bool SdCardAudio::PlaySample( // NOSONAR S5817: const
    uint8_t /* sampleId */)
{
    // NOSONAR TODO SD
    return false;
}

bool SdCardAudio::StreamMusic( //  NOSONAR const TODO
    const std::string& /* filename */)
{
    // NOSONAR TODO SD
    return false;
}
