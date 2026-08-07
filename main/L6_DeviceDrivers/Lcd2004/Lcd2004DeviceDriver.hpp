#pragma once

#include "../../L1_Composition/Context/TasksContext.hpp"
#include "../DeviceDriver.hpp"
#include <cstdint>
#include <string>

class RtosTask;
class I2cDeviceDriver;
class Lcd2004DeviceModel;

class Lcd2004DeviceDriver : public DeviceDriver
{
public:
    static constexpr uint8_t NUMBER_OF_CUSTOM_CHARACTERS = 8;
    static constexpr uint8_t NUMBER_OF_PREDEFINED_CHARACTERS = 2;
    static constexpr uint8_t CUSTOM_CHARACTER_DATA_LENGTH = 8;

    enum class EPredefinedCharacters
    {
        TriangleUp,
        TriangleDown
    };

    Lcd2004DeviceDriver();
    ~Lcd2004DeviceDriver() = default;

    RtosTask& GetRtosTask();
    void SetRtosTask(
        RtosTask& rtosTask);
    void SetI2cDeviceDriver(
        I2cDeviceDriver& i2cDeviceDriver);
    void Initialize() override;

    void Update();
    
private:
    void UpdateCustomCharacters();
    void UpdateCustomCharacter(
        uint8_t slotIndex);

    I2cDeviceDriver& GetI2cDeviceDriver();
    uint8_t GetI2cAddress() const;
    Lcd2004DeviceModel& GetLcd2004DeviceModel();

    void SendDifferentCharacters(
        uint8_t lineIndex);
    void SendFullLine(
        uint8_t lineIndex);

    void PrintChar(
        char c) ;
    void PrintLine(
        std::string_view line);
    void SetCursor(
        uint8_t row, 
        uint8_t column);

	void Command(
        uint8_t cmd);
	void Data(
        uint8_t data);

	void WriteNibble(
        uint8_t nibble,
        uint8_t registerSelect);
	void WriteByte(
        uint8_t byte,
        uint8_t registerSelect);
    
    static constexpr uint8_t LCD_BACKLIGHT = 0x08;
    static constexpr uint8_t LCD_ENABLE    = 0x04;
    static constexpr uint8_t LCD_RS        = 0x01;

    RtosTask* _rtosTask;
    I2cDeviceDriver* _i2cDeviceDriver; 

    static uint8_t _characterData[][CUSTOM_CHARACTER_DATA_LENGTH]; // NOSONAR: ESP32 expects uint8_t
};
