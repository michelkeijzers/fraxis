#include "Displays.hpp"
#include "../../../L9_Utilities/Assert/Assert.hpp"

Displays::Displays()
    : _lcd2004(), _tm1637CentralPanel(), _tm1637Player1(), _tm1637Player2() 
{
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

Tm1637& Displays::GetTm1637ById(Types::ETm1637Id tm1637Id)
{
    Tm1637& tm1637 = _tm1637CentralPanel;

    switch (tm1637Id)
    {
    case Types::ETm1637Id::CentralPanel: tm1637 = _tm1637CentralPanel; break;
    case Types::ETm1637Id::Player1:      tm1637 = _tm1637Player1;      break;
    case Types::ETm1637Id::Player2:      tm1637 = _tm1637Player2;      break;
    default: Assert::Fail("Illegal TM1637 ID"); break;
    }
    return tm1637;
}
