#pragma once

#include "../../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../../M40_DomainModels/I2c/Displays/Tm1637/Tm1637.hpp"
#include "../../M40_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../../M40_DomainModels/Spi/MicroSdCard/MicroSdCard.hpp"
#include "../../M40_DomainModels/Audio/Microphone/Inmp1441.hpp"
#include "../../M40_DomainModels/Audio/Dac/Max53987a.hpp"
#include "../../M40_DomainModels/Audio/Buzzer/Buzzer.hpp"
#include <memory>

class DomainModelsContext
{
public:
    DomainModelsContext() = default;

    DomainModelsContext(const DomainModelsContext&) = delete;
    DomainModelsContext& operator=(const DomainModelsContext&) = delete;
    DomainModelsContext(DomainModelsContext&&) = default;
    DomainModelsContext& operator=(DomainModelsContext&&) = default;

    ~DomainModelsContext() = default;

    void Set(
        std::unique_ptr<Lcd2004> lcd2004,
        std::unique_ptr<Tm1637> tm1637CentralPanel,
        std::unique_ptr<Tm1637> tm1637Player1,
        std::unique_ptr<Tm1637> tm1637Player2,
        std::unique_ptr<IoPins> ioPins,
        std::unique_ptr<LedStrips> ledStrips,
        std::unique_ptr<MicroSdCard> microSdCard,
        std::unique_ptr<Inmp1441> microphone,
        std::unique_ptr<Max53987a> dac,
        std::unique_ptr<Buzzer> buzzer);

    Lcd2004& GetLcd2004();
    Tm1637& GetTm1637CentralPanel();
    Tm1637& GetTm1637Player1();
    Tm1637& GetTm1637Player2();
    IoPins& GetIoPins();
    LedStrips& GetLedStrips();
    MicroSdCard& GetMicroSdCard();
    Inmp1441& GetMicrophone();
    Max53987a& GetDac();
    Buzzer& GetBuzzer();

private:
    std::unique_ptr<Lcd2004> _lcd2004 = nullptr;
    std::unique_ptr<Tm1637> _tm1637CentralPanel = nullptr;
    std::unique_ptr<Tm1637> _tm1637Player1 = nullptr;
    std::unique_ptr<Tm1637> _tm1637Player2 = nullptr;
    std::unique_ptr<IoPins> _ioPins = nullptr;
    std::unique_ptr<LedStrips> _ledStrips = nullptr;
    std::unique_ptr<MicroSdCard> _microSdCard = nullptr;
    std::unique_ptr<Inmp1441> _microphone = nullptr;
    std::unique_ptr<Max53987a> _dac = nullptr;
    std::unique_ptr<Buzzer> _buzzer = nullptr;
};
