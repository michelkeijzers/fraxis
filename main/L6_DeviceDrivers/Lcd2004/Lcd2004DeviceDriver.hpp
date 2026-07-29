#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>
#include <string>

class I2cDeviceDriver;
class Lcd2004DeviceModel;

class Lcd2004DeviceDriver : public DeviceDriver
{
public:
    Lcd2004DeviceDriver();
    ~Lcd2004DeviceDriver();

    void SetI2cDeviceDriver(I2cDeviceDriver& i2cDeviceDriver);

    void SendToDisplay();
    
protected:
    I2cDeviceDriver& GetI2cDeviceDriver();
    uint8_t GetI2cAddress();
    Lcd2004DeviceModel& GetLcd2004DeviceModel();
    
    virtual void PrintChar(char c) = 0;
    virtual void PrintLine(std::string line) = 0;
    virtual void SetCursor(uint8_t row, uint8_t column) = 0;

private:
    void SendDifferentCharacters(uint8_t lineIndex);
    void SendFullLine(uint8_t lineIndex);
    
    I2cDeviceDriver* _i2cDeviceDriver; 
    uint8_t _i2cAddress;
};
