#pragma once

#include "../DeviceDriver.hpp"
#include "../../M10_Composition/Context/TasksContext.hpp"
#include "../../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
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

    enum class EPredefinedCharacters : uint8_t
    {
        TriangleUp,
        TriangleDown
    };

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Lcd2004DeviceDriver();

    Lcd2004DeviceDriver(const Lcd2004DeviceDriver&) = delete;
    Lcd2004DeviceDriver& operator=(const Lcd2004DeviceDriver&) = delete;
    Lcd2004DeviceDriver(Lcd2004DeviceDriver&&) = delete;
    Lcd2004DeviceDriver& operator=(Lcd2004DeviceDriver&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~Lcd2004DeviceDriver() override;

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
    [[nodiscard]] uint8_t GetI2cAddress() const;
    Lcd2004DeviceModel& GetLcd2004DeviceModel();

    void SendDifferentCharacters(
        uint8_t lineIndex);

    void SendFullLine(
        uint8_t lineIndex);

    void PrintChar(
        char character) ;

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

    static std::array<std::array<uint8_t, Lcd2004::CUSTOM_CHARACTER_DATA_LENGTH>,
        Lcd2004::NR_OF_CUSTOM_CHARACTERS> _characterData;
};
