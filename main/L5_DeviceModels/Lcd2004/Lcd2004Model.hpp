#pragma once

#include "../DeviceModel.hpp"
#include <cstdint>
#include <string>

class I2cModel;

class Lcd2004Model : public DeviceModel
{
public:
    Lcd2004Model();
    ~Lcd2004Model();

    void SetI2cModel(I2cModel& i2cModel);
    void Initialize() override;

    void WriteLine(uint8_t line, std::string lineContent);

private:
    I2cModel* _i2cModel;
    uint8_t _i2cAddress;

    std::string _lines[4];
};
