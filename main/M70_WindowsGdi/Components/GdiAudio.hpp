#pragma once

#include <cstdint>
#include <vector>

class GdiAudio
{
public:
    GdiAudio();
    ~GdiAudio() = default;

    void Render(
        int x,
        int y,
        int width,
        int height);

    void SetInputData(
        const std::vector<int16_t>& data);

private:
    std::vector<int16_t> _inputData;
};
