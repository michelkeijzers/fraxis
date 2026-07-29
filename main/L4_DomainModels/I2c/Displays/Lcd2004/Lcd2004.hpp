#pragma once

#include "../../../DomainModel.hpp"
#include <cstdint>
#include <string>

class Lcd2004DeviceModel;

class Lcd2004 : public DomainModel
{
public:
    static const uint8_t LINE_WIDTH = 20;

    Lcd2004();
    ~Lcd2004();

    void SetDeviceModel(IDeviceModel& deviceModel) override;

    void SetLine(uint8_t lineNumber, std::string_view line);

    Lcd2004DeviceModel& GetLcd2004DeviceModel();

private:
    std::string _lines[4];
    // TODO bool _screenEnabled;
    //uint8_t _cursorX;
    //uint8_t _cursorY;
    //bool _cursorEnabled;

    Lcd2004DeviceModel* _lcd2004DeviceModel;
};
