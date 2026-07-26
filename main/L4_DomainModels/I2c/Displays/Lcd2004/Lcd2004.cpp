#include "Lcd2004.hpp"
#include "../../../../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../../../../L5_DeviceModels/Lcd2004/Lcd2004Model.hpp"

Lcd2004::Lcd2004()
{
}

Lcd2004::~Lcd2004()
{
}

void Lcd2004::SetDeviceModelsContext(DeviceModelsContext& deviceModelsContext)
{
    _deviceModelsContext = &deviceModelsContext;
}
    
void Lcd2004::WriteLine(uint8_t lineNumber, std::string line)
{
    _lines[lineNumber] = line;
    _deviceModelsContext->GetLcd2004Model().SetLine(lineNumber, line);
}
