#include "DomainModelsContext.hpp"

void DomainModelsContext::Set( // NOSONAR S107: >= 7 parameters
    std::unique_ptr<Lcd2004> lcd2004,
    std::unique_ptr<Tm1637> tm1637CentralPanel,
    std::unique_ptr<Tm1637> tm1637Player1,
    std::unique_ptr<Tm1637> tm1637Player2,
    std::unique_ptr<IoPins> ioPins, 
    std::unique_ptr<LedStrips> ledStrips,
    std::unique_ptr<MicroSdCard> microSdCard,
    std::unique_ptr<Inmp1441> microphone,
    std::unique_ptr<Max53987a> dac,
    std::unique_ptr<Buzzer> buzzer)
{
    _lcd2004 = std::move(lcd2004);
    _tm1637CentralPanel = std::move(tm1637CentralPanel);
    _tm1637Player1 = std::move(tm1637Player1);
    _tm1637Player2 = std::move(tm1637Player2);
    _ioPins = std::move(ioPins);
    _ledStrips = std::move(ledStrips);
    _microSdCard = std::move(microSdCard);
    _microphone = std::move(microphone);
    _dac = std::move(dac);
    _buzzer = std::move(buzzer);
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

Inmp1441& DomainModelsContext::GetMicrophone()
{
    return *_microphone;
}

Max53987a& DomainModelsContext::GetDac()
{
    return *_dac;
}

Buzzer& DomainModelsContext::GetBuzzer()
{
    return *_buzzer;
}
