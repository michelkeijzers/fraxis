#pragma once

#include "../DeviceModel.hpp"
#include <cstdint>
#include <memory>
#include <vector>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

namespace M50::Ws28xx
{
    class IWs28xxDeviceModel
    {
    public:
        /// @brief RGB struct, but also used for device driver.
        /// @details DO NOT change the order. Despite the name, the order should be green, red blue. 
        /// This is important because the struct is also used inside the device driver to be sent to 
        /// the WS28xx via RMT and the order needs to be specifically in grb order.
        struct RgbStruct
        {
            uint8_t green;

            uint8_t red;

            uint8_t blue;
        };

        virtual ~IWs28xxDeviceModel() = default;

        [[nodiscard]] virtual uint16_t GetNumberOfLeds() const = 0;

        virtual void SetNumberOfLeds(
            uint16_t numberOfLeds) = 0;

        virtual void SetMaxCurrentConsumption(
            uint16_t maxCurrentConsumption) = 0;

        virtual void SetBrightness(
            uint8_t brightness) = 0;

        virtual void SetPixel(
            uint16_t index,
            uint8_t red,
            uint8_t green,
            uint8_t blue) = 0;

        virtual void FillGrbBufferToSend(
            std::vector<IWs28xxDeviceModel::RgbStruct>& rgbBuffer) = 0;

        virtual void SetFrameReady() = 0;

        /// @brief Get leds, only for GDI simulator
        [[nodiscard]] virtual RgbStruct* GetLeds() = 0;
    };
}
