#pragma once

#include "../DeviceModel.hpp"
#include "../../L6_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include <cstdint>
#include <memory>
#include <vector>

class Ws28xxDeviceModel : public DeviceModel
{
public:
    /// @brief RGB struct, but also used for device driver.
    /// @details DO NOT change the order. Despite the name, the order should be green, red blue. because the struct
    /// is also used inside the device driver to be sent to WS28xx via RMT and the order needs to be specifically 
    /// in grb order.
    struct RgbStruct
    {
        uint8_t green;
        uint8_t red;
        uint8_t blue;
    };

    Ws28xxDeviceModel();
    virtual ~Ws28xxDeviceModel();

    uint16_t GetNrOfLeds() const;
    void SetNrOfLeds(uint16_t nrOfLeds);
    void SetMaxCurrentConsumption(uint16_t maxCurrentConsumption);
    void Initialize() override;

    void SetPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
    static bool IsRgbEqual(RgbStruct a, RgbStruct b);

    virtual void FillGrbBufferToSend(std::vector<Ws28xxDeviceModel::RgbStruct>& rgbBuffer);

private:
    std::unique_ptr<RgbStruct[]>  _leds;
    uint16_t _nrOfLeds;
    uint16_t _maxCurrentConsumption;

    RgbStruct CreateRgb(uint8_t red, uint8_t green, uint8_t blue) const;
};
