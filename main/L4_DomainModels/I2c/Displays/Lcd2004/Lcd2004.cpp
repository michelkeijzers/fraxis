#include "Lcd2004.hpp"
#include "../../../../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../../../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../../../L9_Utilities/Assert/Assert.hpp"

Lcd2004::Lcd2004()
: _lcd2004DeviceModel(nullptr)
{
}

void Lcd2004::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _lcd2004DeviceModel = static_cast<Lcd2004DeviceModel*>(&deviceModel);
}
    
void Lcd2004::SetPredefinedCharacter(
    uint8_t slotIndex,
    uint8_t predefinedCharacterIndex)
{
    GetLcd2004DeviceModel().SetPredefinedCharacterIndex(slotIndex, predefinedCharacterIndex);
}

void Lcd2004::SetCustomCharacter(
    uint8_t slotIndex,
    uint8_t data[8])
{
    GetLcd2004DeviceModel().SetCustomCharacterData(slotIndex, data);
}

void Lcd2004::SetLine(
    uint8_t lineNumber, 
    std::string_view line)
{
    Assert::Equals(Types::ETaskId::I2cTask, line.length(), LINE_WIDTH, "Line length must be 20 characters");

    _lines[lineNumber] = std::string(line);
    GetLcd2004DeviceModel().SetLine(lineNumber, line);
}

Lcd2004DeviceModel& Lcd2004::GetLcd2004DeviceModel()
{
    return *_lcd2004DeviceModel;
}
