#include "../../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../../L4_DomainModels/IoPins/IoPins.hpp"
#include "../../L4_DomainModels/Lcd2004/Lcd2004.hpp"
#include "../../L4_DomainModels/Tm1637/Tm1637.hpp"

#include "DomainModelsContext.hpp"

DomainModelsContext::DomainModelsContext() = default;

DomainModelsContext::~DomainModelsContext() = default;

void DomainModelsContext::Set(
    std::unique_ptr<LedStrips> ledStrips,
    std::unique_ptr<IoPins> ioPins,
    std::unique_ptr<Lcd2004> lcd2004,
    std::unique_ptr<Tm1637> tm1637CentralPanel,
    std::unique_ptr<Tm1637> tm1637Player1,
    std::unique_ptr<Tm1637> tm1637Player2)
{
    _ledStrips = std::move(ledStrips);
    _ioPins = std::move(ioPins);
    _lcd2004 = std::move(lcd2004);
    _tm1637CentralPanel = std::move(tm1637CentralPanel);
    _tm1637Player1 = std::move(tm1637Player1);
    _tm1637Player2 = std::move(tm1637Player2);
}
