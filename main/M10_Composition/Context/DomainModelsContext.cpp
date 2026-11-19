#include "DomainModelsContext.hpp"

void DomainModelsContext::Set( // NOSONAR S107: >= 7 parameters
    std::unique_ptr<Lcd2004> lcd2004,
    std::unique_ptr<Tm1637> tm1637CentralPanel,
    std::unique_ptr<Tm1637> tm1637Player1,
    std::unique_ptr<Tm1637> tm1637Player2,
    std::unique_ptr<IoPins> ioPins, 
    std::unique_ptr<LedStrips> ledStrips,
    std::unique_ptr<MicroSdCard> microSdCard,
    std::unique_ptr<I2sMicrophone> i2sMicrophone,
    std::unique_ptr<I2sDac> i2sDac,
    std::unique_ptr<PassiveBuzzer> passiveBuzzer)
{
    _lcd2004 = std::move(lcd2004);
    _tm1637CentralPanel = std::move(tm1637CentralPanel);
    _tm1637Player1 = std::move(tm1637Player1);
    _tm1637Player2 = std::move(tm1637Player2);
    _ioPins = std::move(ioPins);
    _ledStrips = std::move(ledStrips);
    _microSdCard = std::move(microSdCard);
    _i2sMicrophone = std::move(i2sMicrophone);
    _i2sDac = std::move(i2sDac);
    _passiveBuzzer = std::move(passiveBuzzer);
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

MicroSdCard& DomainModelsContext::GetMicroSdCard()
{
    return *_microSdCard; 
}

I2sMicrophone & DomainModelsContext::GetI2sMicrophone()
{
    return *_i2sMicrophone;
}

I2sDac& DomainModelsContext::GetI2sDac()
{
    return *_i2sDac;
}

PassiveBuzzer& DomainModelsContext::GetPassiveBuzzer()
{
    return *_passiveBuzzer;
}
