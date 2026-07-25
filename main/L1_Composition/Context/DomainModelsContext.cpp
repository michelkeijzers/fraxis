#include "../../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../../L4_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../L4_DomainModels/I2c/Displays/Displays.hpp"

#include "DomainModelsContext.hpp"

DomainModelsContext::DomainModelsContext() = default;

DomainModelsContext::~DomainModelsContext() = default;

void DomainModelsContext::Set(
    std::unique_ptr<LedStrips> ledStrips,
    std::unique_ptr<IoPins> ioPins,
    std::unique_ptr<Displays> displays)
{
    _ledStrips = std::move(ledStrips);
    _ioPins = std::move(ioPins);
    _displays = std::move(displays);
}
