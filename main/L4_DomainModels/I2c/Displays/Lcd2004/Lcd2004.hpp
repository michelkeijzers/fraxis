#pragma once

#include <cstdint>
#include <string>

class DeviceModelsContext;

class Lcd2004
{
public:
    static const uint8_t LINE_WIDTH = 20;

    Lcd2004();
    ~Lcd2004();

    void SetDeviceModelsContext(DeviceModelsContext& deviceModelsContext);

    void WriteLine(uint8_t lineNumber, std::string line);

private:
    std::string _lines[4];
    // TODO bool _screenEnabled;
    //uint8_t _cursorX;
    //uint8_t _cursorY;
    //bool _cursorEnabled;

    DeviceModelsContext* _deviceModelsContext;
};
