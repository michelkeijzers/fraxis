#include "Lcd2004DeviceDriver.hpp"

#include "../../L5_DeviceModels/Lcd2004/Lcd2004Model.hpp"
#include "../../L9_Utils/Assert/Assert.hpp"

Lcd2004DeviceDriver::Lcd2004DeviceDriver()
{
}

Lcd2004DeviceDriver::~Lcd2004DeviceDriver()
{
}


void Lcd2004DeviceDriver::SetI2cDeviceDriver(I2cDeviceDriver& i2cDeviceDriver)
{
    _i2cDeviceDriver = &i2cDeviceDriver; 
}


void Lcd2004DeviceDriver::SendToDisplay()
{
    auto* lcd2004Model = static_cast<Lcd2004Model*>(&GetDeviceModel());
    Assert::IsNotNullptr(lcd2004Model, "lcd2004Model");

    if (lcd2004Model->IsCursorDirty())
    {
        //TODO: Cursor command
        lcd2004Model->ClearCursorDirty();
    }

    int8_t dirtyLineIndex = lcd2004Model->GetDirtyLineNumber();
    if (dirtyLineIndex != -1)
    {
        if (lcd2004Model->PerCharacterStrategy(dirtyLineIndex))
        {
            SendDifferentCharacters(dirtyLineIndex);
        }
        else
        {
            SendFullLine(dirtyLineIndex);
        }
        
        lcd2004Model->UpdateLine(dirtyLineIndex);
    }
}

void Lcd2004DeviceDriver::SendDifferentCharacters(uint8_t lineIndex)
{
    auto* lcd2004Model = static_cast<Lcd2004Model*>(&GetDeviceModel());

    const std::string& previousLine = lcd2004Model->GetPreviousLine(lineIndex);
    const std::string& line = lcd2004Model->GetLine(lineIndex);

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
    auto* lcd2004Model = static_cast<Lcd2004Model*>(&GetDeviceModel());
    SetCursor(lineIndex, 0);
    PrintLine(lcd2004Model->GetLine(lineIndex));
}
