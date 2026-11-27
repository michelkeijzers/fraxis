#pragma once

#include <Windows.h>
#include <string>

namespace M50::SevenSegmentsDisplays
{
    class Tm1637DeviceModel;
}

namespace M70::Components
{
    class GdiTm1637
    {
    public:
        GdiTm1637(
            bool hasColon,
            uint16_t x,
            uint16_t y);

        ~GdiTm1637();

        void SetDeviceModel(
            M50::SevenSegmentsDisplays::Tm1637DeviceModel& deviceModel);

        void Update(HDC* hdc);

    private:
        M50::SevenSegmentsDisplays::Tm1637DeviceModel& GetDeviceModel();

        uint16_t D(
            uint16_t value) const;

        std::string GetStringRepresentation();

        bool _hasColon;

        uint16_t _x;
        uint16_t _y;

        HFONT _sevenDigitsFont;

        HBRUSH _backgroundBrush;

        M50::SevenSegmentsDisplays::Tm1637DeviceModel* _deviceModel;
    };
}
