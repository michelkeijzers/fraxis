#pragma once

#include "ILcd2004DeviceDriver.hpp"
#include "../../DeviceDriver.hpp"
#include <cstdint>
#include <array>
#include <string>

namespace M81::RtosTask
{
    class IRtosTask;
}

namespace M60::I2c
{
    class ILcd2004DeviceDriver;
    class II2cDeviceDriver;

    class Lcd2004DeviceDriver : public DeviceDriver, public ILcd2004DeviceDriver
    {
    public:
        enum class EPredefinedCharacters : uint8_t
        {
            TriangleUp,
            TriangleDown
        };

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        Lcd2004DeviceDriver(
            II2cDeviceDriver& i2cDeviceDriver,
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

        Lcd2004DeviceDriver(
            const Lcd2004DeviceDriver&) = delete;
        
        Lcd2004DeviceDriver& operator=(
            const Lcd2004DeviceDriver&) = delete;
        
        Lcd2004DeviceDriver(
            Lcd2004DeviceDriver&&) = delete;
        
        Lcd2004DeviceDriver& operator=(
            Lcd2004DeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~Lcd2004DeviceDriver();

        M81::RtosTask::IRtosTask& GetRtosTask() override;
        
        void SetRtosTask(
            M81::RtosTask::IRtosTask& rtosTask) override;
        
        void Initialize() override;

        void Update() override;

    private:
        void UpdateCustomCharacters();

        void UpdateCustomCharacter(
            uint8_t slotIndex);

        I2c::II2cDeviceDriver& GetI2cDeviceDriver();
        
        [[nodiscard]] uint8_t GetI2cAddress() const;
        
        M50::I2c::Lcd2004DeviceModel& GetLcd2004DeviceModel();

        void SendDifferentCharacters(
            uint8_t lineIndex);

        void SendFullLine(
            uint8_t lineIndex);

        void PrintChar(
            char character);

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
        
        static constexpr uint8_t LCD_ENABLE = 0x04;
        
        static constexpr uint8_t LCD_RS = 0x01;

        M81::RtosTask::IRtosTask* _rtosTask;
        
        I2c::II2cDeviceDriver& _i2cDeviceDriver;

        static std::array<std::array<uint8_t, 
            LCD2004_CUSTOM_CHARACTER_DATA_LENGTH>,
            LCD2004_NUMBER_OF_CUSTOM_CHARACTERS> _characterData;
    };
}
