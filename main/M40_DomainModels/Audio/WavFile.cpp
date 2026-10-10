#include "WavFile.hpp"
#include <fstream>
#include <memory>

WavFile::WavFile()
: _sampleRate(0),
  _bitsPerSample(0),
  _channels(0)
{
}

bool WavFile::Load(
    const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    WavHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(WavHeader));

    if (header.chunkId[0] != 'R' || header.chunkId[1] != 'I' || 
        header.chunkId[2] != 'F' || header.chunkId[3] != 'F')
    {
        return false;
    }

    if (header.format[0] != 'W' || header.format[1] != 'A' || 
        header.format[2] != 'V' || header.format[3] != 'E')
    {
        return false;
    }

    if (header.audioFormat != 1)
    {
        return false;
    }

    _sampleRate = header.sampleRate;
    _bitsPerSample = header.bitsPerSample;
    _channels = header.numChannels;

    size_t dataSize = header.subchunk2Size;
    _data.resize(dataSize / sizeof(int16_t));
    file.read(reinterpret_cast<char*>(_data.data()), dataSize);

    return true;
}

bool WavFile::Save(
    const std::string& filename,
    const int16_t* data,
    size_t length,
    uint32_t sampleRate,
    uint16_t bitsPerSample,
    uint16_t channels)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    WavHeader header = {};
    header.chunkId[0] = 'R';
    header.chunkId[1] = 'I';
    header.chunkId[2] = 'F';
    header.chunkId[3] = 'F';
    header.format[0] = 'W';
    header.format[1] = 'A';
    header.format[2] = 'V';
    header.format[3] = 'E';
    header.subchunk1Id[0] = 'f';
    header.subchunk1Id[1] = 'm';
    header.subchunk1Id[2] = 't';
    header.subchunk1Id[3] = ' ';
    header.subchunk2Id[0] = 'd';
    header.subchunk2Id[1] = 'a';
    header.subchunk2Id[2] = 't';
    header.subchunk2Id[3] = 'a';

    header.audioFormat = 1;
    header.numChannels = channels;
    header.sampleRate = sampleRate;
    header.bitsPerSample = bitsPerSample;
    header.byteRate = sampleRate * channels * (bitsPerSample / 8);
    header.blockAlign = channels * (bitsPerSample / 8);
    header.subchunk1Size = 16;
    header.subchunk2Size = length * sizeof(int16_t);
    header.chunkSize = 36 + header.subchunk2Size;

    file.write(reinterpret_cast<const char*>(&header), sizeof(WavHeader));
    file.write(reinterpret_cast<const char*>(data), length * sizeof(int16_t));

    return true;
}

const int16_t* WavFile::GetData() const
{
    return _data.data();
}

size_t WavFile::GetDataLength() const
{
    return _data.size();
}

uint32_t WavFile::GetSampleRate() const
{
    return _sampleRate;
}

uint16_t WavFile::GetBitsPerSample() const
{
    return _bitsPerSample;
}

uint16_t WavFile::GetChannels() const
{
    return _channels;
}
