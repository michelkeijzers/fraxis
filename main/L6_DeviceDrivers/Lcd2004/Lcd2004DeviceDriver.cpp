#include "Lcd2004DeviceDriver.hpp"

#include "../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

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

I2cDeviceDriver* Lcd2004DeviceDriver::GetI2cDeviceDriver() 
{
    return _i2cDeviceDriver; 
}

uint8_t Lcd2004DeviceDriver::GetI2cAddress() 
{
    return _i2cAddress; 
}

void Lcd2004DeviceDriver::SendToDisplay()
{
    auto* lcd2004DeviceModel = static_cast<Lcd2004DeviceModel*>(&GetDeviceModel());
    Assert::IsNotNullptr(lcd2004DeviceModel, "lcd2004DeviceModel");

    if (lcd2004DeviceModel->IsCursorDirty())
    {
        //TODO: Cursor command
        lcd2004DeviceModel->ClearCursorDirty();
    }

    int8_t dirtyLineIndex = lcd2004DeviceModel->GetDirtyLineNumber();
    if (dirtyLineIndex != -1)
    {
        if (lcd2004DeviceModel->PerCharacterStrategy(dirtyLineIndex))
        {
            SendDifferentCharacters(dirtyLineIndex);
        }
        else
        {
            SendFullLine(dirtyLineIndex);
        }
        
        lcd2004DeviceModel->UpdateLine(dirtyLineIndex);
    }
}

void Lcd2004DeviceDriver::SendDifferentCharacters(uint8_t lineIndex)
{
    auto* lcd2004DeviceModel = static_cast<Lcd2004DeviceModel*>(&GetDeviceModel());

    const std::string& previousLine = lcd2004DeviceModel->GetPreviousLine(lineIndex);
    const std::string& line = lcd2004DeviceModel->GetLine(lineIndex);

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
    auto* lcd2004DeviceModel = static_cast<Lcd2004DeviceModel*>(&GetDeviceModel());
    SetCursor(lineIndex, 0);
    PrintLine(lcd2004DeviceModel->GetLine(lineIndex));
}
