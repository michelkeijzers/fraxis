#pragma once

#include <cstdint>
#include <vector>
#include <string>

class MicroSdCard;

class SdCardAudio
{
public:
    static constexpr uint8_t MAX_SAMPLES = 50;
    static constexpr uint32_t MAX_SAMPLE_SIZE = 1024 * 1024; // 1MB per sample

    SdCardAudio();
    ~SdCardAudio() = default;

    void SetMicroSdCard(
        MicroSdCard& microSdCard);

    bool LoadSample(
        uint8_t sampleId,
        const std::string& filename);

    bool SaveSample(
        uint8_t sampleId,
        const std::string& filename,
        const int16_t* data,
        size_t length);

    const int16_t* GetSample(
        uint8_t sampleId) const;

    size_t GetSampleLength(
        uint8_t sampleId) const;

    bool PlaySample(
        uint8_t sampleId);

    bool StreamMusic(
        const std::string& filename);

private:
    MicroSdCard* _microSdCard;
    std::vector<int16_t> _samples[MAX_SAMPLES];
    std::string _sampleFilenames[MAX_SAMPLES];
};
