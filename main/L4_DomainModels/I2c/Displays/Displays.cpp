#include "Displays.hpp"

Displays::Displays()
    : _lcd2004(), _tm1637CentralPanel(), _tm1637Player1(), _tm1637Player2() 
{
}

void Displays::SetDeviceModelsContext(DeviceModelsContext& deviceModelsContext)
{
    _deviceModelsContext = &deviceModelsContext;
}

Displays::~Displays()
{
}

Lcd2004& Displays::GetLcd2004()
{
    return _lcd2004; 
}

Tm1637& Displays::GetTm1637CentralPanel() 
{
    return _tm1637CentralPanel; 
}

Tm1637& Displays::GetTm1637Player1() 
{
    return _tm1637Player1; 
}

Tm1637& Displays::GetTm1637Player2() 
{
    return _tm1637Player2; 
}
