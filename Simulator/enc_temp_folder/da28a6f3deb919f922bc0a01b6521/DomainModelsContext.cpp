#include "../../L4_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../L4_DomainModels/I2c/Displays/Tm1637/Tm1637.hpp"
#include "../../L4_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../L4_DomainModels/LedStrips/LedStrips.hpp"

#include "DomainModelsContext.hpp"

DomainModelsContext::DomainModelsContext()
:   _lcd2004(nullptr), 
    _tm1637CentralPanel(nullptr), 
    _tm1637Player1(nullptr), 
    _tm1637Player2(nullptr),
    _ioPins(nullptr), 
    _ledStrips(nullptr)
{
}

DomainModelsContext::~DomainModelsContext()
{
}


void DomainModelsContext::Set(
    std::unique_ptr<Lcd2004> lcd2004,
    std::unique_ptr<Tm1637> tm1637CentralPanel,
    std::unique_ptr<Tm1637> tm1637Player1,
    std::unique_ptr<Tm1637> tm1637Player2,
    std::unique_ptr<IoPins> ioPins, 
    std::unique_ptr<LedStrips> ledStrips)
{
    _lcd2004 = std::move(lcd2004);
    _tm1637CentralPanel = std::move(tm1637CentralPanel);
    _tm1637Player1 = std::move(tm1637Player1);
    _tm1637Player2 = std::move(tm1637Player2);
    _ioPins = std::move(ioPins);
    _ledStrips = std::move(ledStrips);
}

Lcd2004& DomainModelsContext::GetLcd2004()
{
    return *_lcd2004;
}

Tm1637& DomainModelsContext::GetTm1637CentralPanel()
{
    return *_tm1637CentralPanel;
}

Tm1637& DomainModelsContext::GetTm1637Player1()
{
    return *_tm1637Player1;
}

Tm1637& DomainModelsContext::GetTm1637Player2()
{
    return *_tm1637Player2;
}

IoPins& DomainModelsContext::GetIoPins()                
{
    return *_ioPins; 
}

LedStrips& DomainModelsContext::GetLedStrips()          
{
    return *_ledStrips; 
}
