#include "../../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../M40_DomainModels/I2c/Displays/Tm1637/Tm1637.hpp"
#include "../../M40_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../../M40_DomainModels/Spi/MicroSdCard/MicroSdCard.hpp"
#include "../../M40_DomainModels/Audio/Microphone/Inmp1441.hpp"
#include "../../M40_DomainModels/Audio/Dac/Max53987a.hpp"
#include "../../M40_DomainModels/Audio/Buzzer/Buzzer.hpp"
#include "DomainModelsContext.hpp"

DomainModelsContext::DomainModelsContext()
:   _lcd2004(nullptr), 
    _tm1637CentralPanel(nullptr), 
    _tm1637Player1(nullptr), 
    _tm1637Player2(nullptr),
    _ioPins(nullptr), 
    _ledStrips(nullptr),
    _microSdCard(nullptr),
    _microphone(nullptr),
    _dac(nullptr),
    _buzzer(nullptr)
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
