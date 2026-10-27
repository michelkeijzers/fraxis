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
    //TODOSD
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
    //TODOSD
    if (sampleId >= MAX_SAMPLES)
    {
        return true;
    }

    return false;
}

const int16_t* SdCardAudio::GetSample(
    uint8_t sampleId) const
{
    //TODOSD
    if (sampleId >= MAX_SAMPLES)
    {
        return nullptr;
    }
    return _samples[sampleId].data();
}

size_t SdCardAudio::GetSampleLength(
    uint8_t sampleId) const
{
    //TODOSD
    if (sampleId >= MAX_SAMPLES)
    {
        return 0;
    }
    return _samples[sampleId].size();
}

bool SdCardAudio::PlaySample( // NOSONAR S5817: const
    uint8_t /* sampleId */)
{
    //TODOSD
    return false;
}

bool SdCardAudio::StreamMusic( //  NOSONAR const TODO
    const std::string& /* filename */)
{
    //TODOSD
    return false;
}
