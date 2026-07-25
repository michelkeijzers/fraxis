#pragma once

#include <cstdint>
#include <string>

class I2cModel;

class Lcd2004Model
{
public:
    Lcd2004Model();
    ~Lcd2004Model();

    void WriteLine(uint8_t line, std::string lineContent);
    void SetI2cModel(I2cModel& i2cModel);

private:
    I2cModel* _i2cModel;

    std::string _lines[4];
};
