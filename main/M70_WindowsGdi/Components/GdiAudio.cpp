#include "GdiAudio.hpp"
#include <windows.h>
#include <mmsystem.h>
#include <vector>

#pragma comment(lib, "winmm.lib")

GdiAudio::GdiAudio()
{
}

void GdiAudio::Render(
    int x,
    int y,
    int width,
    int height)
{
    // Draw audio visualization
    HDC hdc = GetDC(nullptr);
    if (hdc)
    {
        RECT rect = { x, y, x + width, y + height };
        FillRect(hdc, &rect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));

        if (!_inputData.empty())
        {
            int centerY = y + height / 2;
            int step = width / static_cast<int>(_inputData.size());

            for (size_t i = 0; i < _inputData.size(); i++)
            {
                int sample = _inputData[i];
                int barHeight = abs(sample) / 100;
                int barY = centerY - barHeight / 2;

                RECT barRect = { x + i * step, barY, x + (i + 1) * step, barY + barHeight };
                FillRect(hdc, &barRect, static_cast<HBRUSH>(GetStockObject(GREEN_BRUSH)));
            }
        }

        ReleaseDC(nullptr, hdc);
    }
}

void GdiAudio::SetInputData(
    const std::vector<int16_t>& data)
{
    _inputData = data;
}
