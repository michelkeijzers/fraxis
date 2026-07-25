#pragma once

#include "../DeviceModel.hpp"
#include <cstdint>

class I2cModel : public DeviceModel
{
public:
    I2cModel();
    ~I2cModel();

    void Initialize() override;
    
    uint8_t GetClkPin() const;
    uint8_t GetSdaPin() const;
    void SetClkPin(uint8_t pin);
    void SetSdaPin(uint8_t pin);

private:
    uint8_t _clkPin;
    uint8_t _sdaPin;
};
