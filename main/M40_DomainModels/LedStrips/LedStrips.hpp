#pragma once

#include "../DomainModel.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M30_Messages/LedStrips/Color.hpp"
#include "../../M30_Messages/LedStrips/Position.hpp"
#include "../../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include <cstdint>

namespace M50::Ws28xx
{
    class Ws28xxDeviceModel;
}

namespace M90::Algorithm
{
    class IAlgorithm;
}

class LedStrips : public DomainModel
{
public:
    static constexpr uint8_t NUMBER_OF_LED_STRIPS = 5;
    static constexpr uint8_t NUMBER_OF_LEDS_PER_LED_STRIP = 72;
    static constexpr uint16_t NUMBER_OF_LEDS = NUMBER_OF_LED_STRIPS * NUMBER_OF_LEDS_PER_LED_STRIP;

    explicit LedStrips(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::Algorithm::IAlgorithm& algorithm);

    LedStrips(
        const LedStrips&) = delete;

    LedStrips& operator=(
        const LedStrips&) = delete;
    
    LedStrips(
        LedStrips&&) = delete;
    
    LedStrips& operator=(
        LedStrips&&) = delete;

    ~LedStrips() override = default;

    M50::Ws28xx::Ws28xxDeviceModel& GetWs28xxDeviceModel();
    void SetDeviceModel(
        M50::IDeviceModel& deviceModel) override;

    void SetBrightness(
        uint8_t brightness);
        
    void SetPixel(
        Position position,
        Color color);
        
    void SetFrameReady();

    [[nodiscard]] Types::ELedStripsOrientation GetOrientation() const;

private:
    void SwapXyIfVertical(
        Position& position) const;

    uint16_t GetDeviceModelLedIndex(
        Position& position) const;

    // NOLINTNEXTLINE cppcoreguidelines-avoid-c-arrays
    Color _leds[NUMBER_OF_LEDS_PER_LED_STRIP][NUMBER_OF_LED_STRIPS]; // NOSONAR: ESP32 preference
    
    Types::ELedStripsOrientation _orientation;

    M50::Ws28xx::Ws28xxDeviceModel* _ws28xxDeviceModel;

    M90::Algorithm::IAlgorithm &_algorithm;
};
