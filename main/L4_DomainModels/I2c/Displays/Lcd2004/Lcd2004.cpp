#include "Lcd2004.hpp"
#include "../../../../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../../../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../../../L9_Utilities/Assert/Assert.hpp"

Lcd2004::Lcd2004()
: _lcd2004DeviceModel(nullptr)
{
}

Lcd2004::~Lcd2004()
{
}

void Lcd2004::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _lcd2004DeviceModel = static_cast<Lcd2004DeviceModel*>(&deviceModel);
}
    

void Lcd2004::SetLine(
    uint8_t lineNumber, 
    std::string_view line)
{
    Assert::Equals(line.length(), LINE_WIDTH, "Line length must be 20 characters");

    _lines[lineNumber] = line;
    GetLcd2004DeviceModel().SetLine(lineNumber, line);
}

Lcd2004DeviceModel& Lcd2004::GetLcd2004DeviceModel()
{
    return *_lcd2004DeviceModel;
}
