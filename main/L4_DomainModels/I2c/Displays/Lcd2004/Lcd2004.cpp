#include "Lcd2004.hpp"
#include "../../../../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../../../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"

Lcd2004::Lcd2004()
{
}

Lcd2004::~Lcd2004()
{
}

void Lcd2004::SetDeviceModel(IDeviceModel& deviceModel)
{
    _lcd2004DeviceModel = static_cast<Lcd2004DeviceModel*>(&deviceModel);
}
    
void Lcd2004::WriteLine(uint8_t lineNumber, std::string line)
{
    _lines[lineNumber] = line;
    _lcd2004DeviceModel->SetLine(lineNumber, line);
}
