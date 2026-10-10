#pragma once

#include <cstdint>
#include <vector>
#include <string>

class WavFile
{
public:
    struct WavHeader
    {
        char chunkId[4];
        uint32_t chunkSize;
        char format[4];
        char subchunk1Id[4];
        uint32_t subchunk1Size;
        uint16_t audioFormat;
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;
        char subchunk2Id[4];
        uint32_t subchunk2Size;
    };

    WavFile();
    ~WavFile() = default;

    bool Load(
        const std::string& filename);

    bool Save(
        const std::string& filename,
        const int16_t* data,
        size_t length,
        uint32_t sampleRate,
        uint16_t bitsPerSample,
        uint16_t channels);

    const int16_t* GetData() const;
    size_t GetDataLength() const;
    uint32_t GetSampleRate() const;
    uint16_t GetBitsPerSample() const;
    uint16_t GetChannels() const;

private:
    std::vector<int16_t> _data;
    uint32_t _sampleRate;
    uint16_t _bitsPerSample;
    uint16_t _channels;
};
