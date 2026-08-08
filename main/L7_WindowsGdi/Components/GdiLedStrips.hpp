#pragma once

#include <cstdint>
#include <Windows.h>
#include <array>

class Ws28xxDeviceModel;

/// @brief: GDI Led strips class
/// @details: To prevent during an update (at 60 FPS typically) to create a SolidBrsh for every 
/// LED (360 time 60 = 21,600), a fixed set of brushes will be created.
/// These brushes will have RGB values with one of the following values:
/// Index:  0   1  2    3   4   5   6   7   8   9   10  11  12  13  14 
/// Value:  0   4  8   16  32  48  64  80  96  112 128 160 192 224 255
/// Diff:   0  +4 +4   +8 +16 +16 +16 +16 +16  +16 +16 +32 +32 +32 +31
/// 
/// This resuls in 15 (red) * 15 (green) * 15 (blue) =  3,375 brushes.
/// The method FindBrush(red, green, blue) will be used to find the best matching brush.
class GdiLedStrips
{
public:
    GdiLedStrips(
        uint16_t x,
        uint16_t y);
    ~GdiLedStrips();

    Ws28xxDeviceModel& GetDeviceModel();
    void SetDeviceModel(
        Ws28xxDeviceModel& deviceModel);

    void Update(
        HDC* hdc);

private:
    static constexpr uint8_t LEVELS[15] = { // NOSONAR: No strings (?)
        0, 4, 8, 16, 32, 48, 64, 80, 96, 112, 128, 160, 192, 224, 255
    };

    uint16_t D(
        uint16_t value) const;
    void CreateBrushes();
    HBRUSH& FindBrush(
        uint8_t red,
        uint8_t green,
        uint8_t blue);
    uint8_t Quantize(
        uint8_t colorValue) const;
    uint8_t BrushIndex(
        uint8_t redIndex, 
        uint8_t greenIndex, 
        uint8_t blueIndex) const;

    uint16_t _x;
    uint16_t _y;

    std::array<HBRUSH, 3375> _ledBrushes;
    HBRUSH _ledBackgroundBrush;

    Ws28xxDeviceModel* _deviceModel;
};
