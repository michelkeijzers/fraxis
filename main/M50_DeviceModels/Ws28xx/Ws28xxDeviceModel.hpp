#pragma once

#include "../DeviceModel.hpp"
#include "IWs28xxDeviceModel.hpp"
#include <cstdint>
#include <memory>
#include <vector>

namespace M50::Ws28xx
{
    class Ws28xxDeviceModel : public DeviceModel, public IWs28xxDeviceModel
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        Ws28xxDeviceModel(
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log,
            M90::String::IStringUtilities& stringUtilities);

        Ws28xxDeviceModel(
            const Ws28xxDeviceModel&) = delete;

        Ws28xxDeviceModel& operator=(
            const Ws28xxDeviceModel&) = delete;

        Ws28xxDeviceModel(
            Ws28xxDeviceModel&&) = delete;

        Ws28xxDeviceModel& operator=(
            Ws28xxDeviceModel&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~Ws28xxDeviceModel() override;

        [[nodiscard]] uint16_t GetNumberOfLeds() const override;
        
        void SetNumberOfLeds(
            uint16_t numberOfLeds) override;

        void SetMaxCurrentConsumption(
            uint16_t maxCurrentConsumption) override;

        void Initialize() override;

        void SetBrightness(
            uint8_t brightness) override;

        void SetPixel(
            uint16_t index,
            uint8_t red,
            uint8_t green,
            uint8_t blue) override;

        [[nodiscard]] static bool IsRgbEqual(
            RgbStruct rgb1,
            RgbStruct rgb2);

        virtual void FillGrbBufferToSend(
            std::vector<Ws28xxDeviceModel::RgbStruct>& rgbBuffer) override;

        void SetFrameReady() override;

        /// @brief Get leds, only for GDI simulator
        [[nodiscard]] RgbStruct* GetLeds() override;

    private:
        uint8_t _brightness;

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, modernize-avoid-c-arrays)
        std::unique_ptr<RgbStruct[]> _leds; // NOSONAR, Keep RgbStruct over std::vector for performance

        uint16_t _numberOfLeds;

        uint16_t _maxCurrentConsumption;

        bool _frameReady;

        [[nodiscard]] RgbStruct CreateRgb(
            uint8_t red,
            uint8_t green,
            uint8_t blue) const;
    };
}
