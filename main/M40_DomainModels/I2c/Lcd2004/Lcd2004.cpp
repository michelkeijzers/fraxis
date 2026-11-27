#include "Lcd2004.hpp"
#include "../../../M50_DeviceModels/I2c/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../../M90_Utilities/Assert/IAssert.hpp"

Lcd2004::Lcd2004(
    M50::I2c::ILcd2004DeviceModel& lcd2004DeviceModel,
    M50::IDeviceModel& deviceModel,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
: 
    DomainModel(deviceModel, assert, log),
    _assert(assert),
    _lcd2004DeviceModel(lcd2004DeviceModel)
{
    // No functionality required
}

void Lcd2004::SetPredefinedCharacter(
    uint8_t slotIndex,
    uint8_t predefinedCharacterIndex)
{
    GetLcd2004DeviceModel().SetPredefinedCharacterIndex(slotIndex, predefinedCharacterIndex);
}

void Lcd2004::SetCustomCharacter(
    uint8_t slotIndex,
    std::array<uint8_t, CUSTOM_CHARACTER_DATA_LENGTH> data)
{
    GetLcd2004DeviceModel().SetCustomCharacterData(slotIndex, data);
}

void Lcd2004::SetLine(
    uint8_t lineNumber, 
    std::string_view line)
{
    _assert.Equals(
        Types::ETaskId::I2cTask, 
        static_cast<uint8_t>(line.length()), 
        LINE_WIDTH, 
        "Line length must be 20 characters");

    _lines[lineNumber] = std::string(line);
    GetLcd2004DeviceModel().SetLine(lineNumber, line);
}

M50::I2c::ILcd2004DeviceModel& Lcd2004::GetLcd2004DeviceModel()
{
    return _lcd2004DeviceModel;
}
