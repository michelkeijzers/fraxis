#pragma once

#include "../../../DomainModel.hpp"
#include <cstdint>
#include <string>
#include <array>

class Lcd2004DeviceModel;

class Lcd2004 : public DomainModel
{
public:
    static constexpr uint8_t NUMBER_OF_LINES = 4;
    static constexpr uint8_t LINE_WIDTH = 20;

    Lcd2004();
    ~Lcd2004() = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

    void SetLine(
        uint8_t lineNumber,
        std::string_view line);

    Lcd2004DeviceModel& GetLcd2004DeviceModel();

private:
    std::array<std::string, NUMBER_OF_LINES> _lines;
    /// TO DO FUTURE: Add cursor/screen enabled
    /// bool _screenEnabled;
    /// uint8_t _cursorX;
    /// uint8_t _cursorY;
    /// bool _cursorEnabled;

    Lcd2004DeviceModel* _lcd2004DeviceModel;
};
