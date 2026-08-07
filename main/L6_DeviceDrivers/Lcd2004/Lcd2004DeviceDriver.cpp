#include "Lcd2004DeviceDriver.hpp"

#include "../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../L6_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../../L8_Services/RtosTask/RtosTask.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"


/* static */ uint8_t Lcd2004DeviceDriver::          // NOSONAR: ESP32 prefers uint8_t
    _characterData[][CUSTOM_CHARACTER_DATA_LENGTH] =
{
    {
        // ▲ Triangle up, alt 30 or U+25B2
        0x04, // 00100
        0x0E, // 01110
        0x1F, // 11111
        0x00, // 00000
        0x00, // 00000
        0x00, // 00000
        0x00, // 00000
        0x00, // 00000
    },
    {
        // ▼ Triangle down, alt 31 or U+25BC
        0x00, // 00000
        0x00, // 00000
        0x00, // 00000
        0x00, // 00000
        0x00, // 00000
        0x1F, // 11111
        0x0E, // 01110
        0x04, // 00100
    }
};

Lcd2004DeviceDriver::Lcd2004DeviceDriver()
:   _rtosTask(nullptr),
    _i2cDeviceDriver(nullptr)
{
}

RtosTask& Lcd2004DeviceDriver::GetRtosTask() 
{
    return *_rtosTask; 
}

void Lcd2004DeviceDriver::SetRtosTask(
    RtosTask& rtosTask) 
{
    _rtosTask = &rtosTask; 
}

I2cDeviceDriver& Lcd2004DeviceDriver::GetI2cDeviceDriver() 
{
    return *_i2cDeviceDriver; 
}

void Lcd2004DeviceDriver::SetI2cDeviceDriver(
    I2cDeviceDriver& i2cDeviceDriver)
{
    _i2cDeviceDriver = &i2cDeviceDriver; 
}

void Lcd2004DeviceDriver::Initialize()
{
    Assert::IsNot0(GetI2cAddress(), "I2C address not set");
    GetRtosTask().DelayTask(50);

	// 4‑bit init sequence
	WriteNibble(0x30, 0);
    GetRtosTask().DelayTask(5);

	WriteNibble(0x30, 0);
    GetRtosTask().DelayTask(1);

	WriteNibble(0x20, 0);

	Command(0x28); // 4‑bit, 4 lines
	Command(0x0C); // display on
	Command(0x06); // entry mode
	Command(0x01); // clear
    GetRtosTask().DelayTask(2);

    MarkInitialized();
}

uint8_t Lcd2004DeviceDriver::GetI2cAddress() const
{
    return (static_cast<Lcd2004DeviceModel&>(GetDeviceModel()).GetI2cAddress());
}

Lcd2004DeviceModel& Lcd2004DeviceDriver::GetLcd2004DeviceModel() 
{
    return static_cast<Lcd2004DeviceModel&>(GetDeviceModel()); 
}

void Lcd2004DeviceDriver::Update()
{
    Assert::IsTrue(IsInitialized());
    
    auto& lcd2004DeviceModel = GetLcd2004DeviceModel();
    UpdateCustomCharacters();

    if (GetLcd2004DeviceModel().IsCursorDirty())
    {
        /// @todo: Later: Add Cursor command
        lcd2004DeviceModel.ClearCursorDirty();
    }

    int8_t dirtyLineIndex = lcd2004DeviceModel.GetDirtyLineNumber();
    if (dirtyLineIndex != -1)
    {
        if (lcd2004DeviceModel.PerCharacterStrategy(dirtyLineIndex))
        {
            SendDifferentCharacters(dirtyLineIndex);
        }
        else
        {
            SendFullLine(dirtyLineIndex);
        }
        
        lcd2004DeviceModel.UpdateLine(dirtyLineIndex);
    }
}

void Lcd2004DeviceDriver::UpdateCustomCharacters()
{
    auto& lcd2004DeviceModel = GetLcd2004DeviceModel();

    for (uint8_t slotIndex = 0; slotIndex < NUMBER_OF_CUSTOM_CHARACTERS; slotIndex++)
    {
        if (lcd2004DeviceModel.IsCharacterDirty(slotIndex))
        {
            UpdateCustomCharacter(slotIndex);
        }
        SetCursor(0, 0);
        lcd2004DeviceModel.ClearCharacterDirty(slotIndex);
    }
}

void Lcd2004DeviceDriver::UpdateCustomCharacter(
    uint8_t slotIndex)
{
    auto& lcd2004DeviceModel = GetLcd2004DeviceModel();
 
    Command((uint8_t)(0x40 | (slotIndex << 3))); // NOSONAR: ESP32 prefers uint8_t
    if (lcd2004DeviceModel.IsPredefinedCharacter(slotIndex))
    {
        for (uint8_t rowIndex = 0; rowIndex < CUSTOM_CHARACTER_DATA_LENGTH; rowIndex++)
        {
            Data(_characterData[
                lcd2004DeviceModel.GetPredefinedCharacterIndex(slotIndex)][rowIndex]);
        }
    }
    else // Custom character
    {
        for (uint8_t rowIndex = 0; rowIndex < CUSTOM_CHARACTER_DATA_LENGTH; rowIndex++)
        {
            Data(lcd2004DeviceModel.GetCustomCharacterData(slotIndex, rowIndex));
        }
    }
}

void Lcd2004DeviceDriver::SendDifferentCharacters(
    uint8_t lineIndex)
{
    auto& lcd2004DeviceModel = GetLcd2004DeviceModel();

    const std::string_view& previousLine = lcd2004DeviceModel.GetPreviousLine(lineIndex);
    const std::string_view& line = lcd2004DeviceModel.GetLine(lineIndex);

    int8_t cursorPosition = -1;

    Assert::Equals(previousLine.length(), line.length(), "Previous/Line");
    for (uint8_t index = 0; index < line.length(); index++)
    {
        if (previousLine[index] != line[index]) 
        {
            if (cursorPosition != index)
            {
                SetCursor(lineIndex, index);
                cursorPosition = index;
            }
            PrintChar(line[index]);
            cursorPosition++;
        }
    }
}

void Lcd2004DeviceDriver::SendFullLine(
    uint8_t lineIndex)
{
    auto& lcd2004DeviceModel = GetLcd2004DeviceModel();
    SetCursor(lineIndex, 0);
    PrintLine(lcd2004DeviceModel.GetLine(lineIndex));
}


void Lcd2004DeviceDriver::PrintChar(char characterToPrint)
{
    Data(characterToPrint);
}

void Lcd2004DeviceDriver::PrintLine(
    std::string_view line)
{
    for (uint8_t index = 0; index < line.length(); index++)
	{
        PrintChar(line[index]);
	}
}

void Lcd2004DeviceDriver::SetCursor(
    uint8_t row, 
    uint8_t column) 
{
    static constexpr uint8_t ROW_OFFSETS[] = {0x00, 0x40, 0x14, 0x54}; // LCD2004
    Command(0x80 | (ROW_OFFSETS[row] + column));
}

void Lcd2004DeviceDriver::Command(uint8_t cmd)
{
    WriteByte(cmd, 0);
}

void Lcd2004DeviceDriver::Data(uint8_t data)
{
    WriteByte(data, 1);
}

void Lcd2004DeviceDriver::WriteNibble(
    uint8_t nibble,
    uint8_t registerSelect)
{
    uint8_t data = nibble | LCD_BACKLIGHT | (registerSelect ? LCD_RS : 0); // NOSONAR ESP32 prefers uint8_t
    uint8_t buf[3] = { data, static_cast<uint8_t>(data | LCD_ENABLE), data }; // NOSONAR ESP32 prefers uint8_t
    GetI2cDeviceDriver().Write(GetI2cAddress(), buf, sizeof(buf));
}

void Lcd2004DeviceDriver::WriteByte(
    uint8_t byte, 
    uint8_t registerSelect)
{
    WriteNibble(byte & 0xF0, registerSelect); // NOSONAR ESP32 prefers uint8_t
    WriteNibble((byte << 4) & 0xF0, registerSelect); // NOSONAR ESP32 prefers uint8_t
}