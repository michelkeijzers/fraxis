#include "Lcd2004DeviceDriver.hpp"

#include "../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../L6_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../../L8_Services/RtosTask/RtosTask.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

Lcd2004DeviceDriver::Lcd2004DeviceDriver()
{
}

Lcd2004DeviceDriver::~Lcd2004DeviceDriver()
{
}

RtosTask& Lcd2004DeviceDriver::GetRtosTask() 
{
    return *_rtosTask; 
}

void Lcd2004DeviceDriver::SetRtosTask(RtosTask& rtosTask) 
{
    _rtosTask = &rtosTask; 
}

I2cDeviceDriver& Lcd2004DeviceDriver::GetI2cDeviceDriver() 
{
    return *_i2cDeviceDriver; 
}

void Lcd2004DeviceDriver::SetI2cDeviceDriver(I2cDeviceDriver& i2cDeviceDriver)
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
}

uint8_t Lcd2004DeviceDriver::GetI2cAddress() 
{
    return _i2cAddress; 
}

Lcd2004DeviceModel& Lcd2004DeviceDriver::GetLcd2004DeviceModel() 
{
    return static_cast<Lcd2004DeviceModel&>(GetDeviceModel()); 
}

void Lcd2004DeviceDriver::SendToDisplay()
{
    auto& lcd2004DeviceModel = GetLcd2004DeviceModel();

    if (GetLcd2004DeviceModel().IsCursorDirty())
    {
        //TODO: Cursor command
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

void Lcd2004DeviceDriver::SendDifferentCharacters(uint8_t lineIndex)
{
    auto& lcd2004DeviceModel = GetLcd2004DeviceModel();

    const std::string_view& previousLine = lcd2004DeviceModel.GetPreviousLine(lineIndex);
    const std::string_view& line = lcd2004DeviceModel.GetLine(lineIndex);

    int8_t cursorPosition = -1;
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

void Lcd2004DeviceDriver::SendFullLine(uint8_t lineIndex)
{
    auto& lcd2004DeviceModel = GetLcd2004DeviceModel();
    SetCursor(lineIndex, 0);
    PrintLine(lcd2004DeviceModel.GetLine(lineIndex));
}


void Lcd2004DeviceDriver::PrintChar(char characterToPrint)
{
    Data(characterToPrint);
}

void Lcd2004DeviceDriver::PrintLine(std::string_view line)
{
    for (uint8_t index = 0; index < line.length(); index++)
	{
        PrintChar(line[index]);
	}
}

void Lcd2004DeviceDriver::SetCursor(uint8_t row, uint8_t column) 
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

void Lcd2004DeviceDriver::WriteNibble(uint8_t nibble, uint8_t registerSelect)
{
    uint8_t data = nibble | LCD_BACKLIGHT | (registerSelect ? LCD_RS : 0);
    uint8_t buf[3] = { data, static_cast<uint8_t>(data | LCD_ENABLE), data };
    GetI2cDeviceDriver().Write(GetI2cAddress(), buf, sizeof(buf));
}

void Lcd2004DeviceDriver::WriteByte(uint8_t byte, uint8_t registerSelect)
{
    WriteNibble(byte & 0xF0, registerSelect);
    WriteNibble((byte << 4) & 0xF0, registerSelect);
}