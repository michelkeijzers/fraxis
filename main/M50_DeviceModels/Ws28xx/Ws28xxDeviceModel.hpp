#pragma once

#include "../DeviceModel.hpp"
#include "../../M60_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include <cstdint>
#include <memory>
#include <vector>
#include <span>

class Ws28xxDeviceModel : public DeviceModel
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

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Ws28xxDeviceModel();

    Ws28xxDeviceModel(const Ws28xxDeviceModel&) = delete;
    Ws28xxDeviceModel& operator=(const Ws28xxDeviceModel&) = delete;
    Ws28xxDeviceModel(Ws28xxDeviceModel&&) = delete;
    Ws28xxDeviceModel& operator=(Ws28xxDeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~Ws28xxDeviceModel() override;

    [[nodiscard]] uint16_t GetNrOfLeds() const;
    void SetNrOfLeds(
        uint16_t nrOfLeds);

    void SetMaxCurrentConsumption(
        uint16_t maxCurrentConsumption);

    void Initialize() override;

    void SetBrightness(
        uint8_t brightness);

    void SetPixel(
        uint16_t index,
        uint8_t red,
        uint8_t green,
        uint8_t blue);

    [[nodiscard]] static bool IsRgbEqual(
        RgbStruct rgb1, 
        RgbStruct rgb2);

    virtual void FillGrbBufferToSend(
        std::vector<Ws28xxDeviceModel::RgbStruct>& rgbBuffer);

    void SetFrameReady();

    /// @brief Get leds, only for GDI simulator
    [[nodiscard]] RgbStruct* GetLeds();

private:
    uint8_t _brightness;
    
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, modernize-avoid-c-arrays)
    std::unique_ptr<RgbStruct[]> _leds; // NOSONAR, Keep RgbStruct over std::vector for performance
    uint16_t _nrOfLeds;
    uint16_t _maxCurrentConsumption;
    bool _frameReady;

    [[nodiscard]] RgbStruct CreateRgb(
        uint8_t red, 
        uint8_t green, 
        uint8_t blue) const;
};
