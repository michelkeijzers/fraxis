#pragma once

#include "../IGdiMouseInput.hpp"
#include "../../M90_Utilities/Math/BitUtilities.hpp"
#include <cstdint>
#include <Windows.h>
#include <string>


namespace M60::I2c
{
    class IMcp23017DeviceDriver;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M70::Components
{
    class GdiButton : public IGdiMouseInput
    {
    public:
        GdiButton(
            M90::Assert::IAssert& assert,
            std::string_view text,
            uint8_t bitNumber,
            int x,
            int y);

        ~GdiButton();

        M60::I2c::IMcp23017DeviceDriver& GetDeviceDriver();

        void SetDeviceDriver(
            M60::I2c::IMcp23017DeviceDriver& deviceDriver);

        void TriggerState(
            bool state);

        bool HitTest(int x, int y) override;

        void OnMouseDown(int x, int y) override;

        void OnMouseMove(int x, int y) override;

        void OnMouseUp(int x, int y) override;

        void Update(HDC* hdc);

    private:
        M90::Assert::IAssert& _assert;

        void SimulateBit(
            bool on);

        uint16_t D(
            uint16_t value) const;

        HBRUSH GetBrush(
            bool pressed);

        std::string _text;

        uint8_t _bitNumber;

        int _x;
        int _y;

        bool _pressed;

        bool _hovered;

        HFONT _font;

        HBRUSH _normalBrush;
        HBRUSH _hoverBrush;
        HBRUSH _pressedBrush;

        HPEN _borderPen;

        M60::I2c::IMcp23017DeviceDriver* _deviceDriver;

        M90::Math::BitUtilities _bitUtilities;
    };
}
