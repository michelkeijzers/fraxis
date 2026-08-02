#pragma once

#include "Lcd2004/Lcd2004.hpp"
#include "Tm1637/Tm1637.hpp"
#include "../../../L3_Messages/Types.hpp"

class DeviceModelsContext;

class Displays
{
public:
    Displays();
    ~Displays();

    Lcd2004& GetLcd2004();
    Tm1637& GetTm1637CentralPanel();
    Tm1637& GetTm1637Player1();
    Tm1637& GetTm1637Player2();

    Tm1637& GetTm1637ById(Types::ETm1637Id tm1637Id);

private:
    Lcd2004 _lcd2004;
    Tm1637 _tm1637CentralPanel;
    Tm1637 _tm1637Player1;
    Tm1637 _tm1637Player2;
};
