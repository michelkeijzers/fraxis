#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>
#include <string>

class I2cDeviceDriver;

class Lcd2004DeviceDriver : public DeviceDriver
{
public:
    Lcd2004DeviceDriver();
    ~Lcd2004DeviceDriver();

    void SetI2cDeviceDriver(I2cDeviceDriver& i2cDeviceDriver);

    void SendToDisplay();
    
protected:
    I2cDeviceDriver* _i2cDeviceDriver; 

    virtual void PrintChar(char c) = 0;
    virtual void PrintLine(std::string line) = 0;
    virtual void SetCursor(uint8_t row, uint8_t column) = 0;

private:
    void SendDifferentCharacters(uint8_t lineIndex);
    void SendFullLine(uint8_t lineIndex);
};
