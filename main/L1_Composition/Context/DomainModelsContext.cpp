#include "../../L4_DomainModels/I2c/Displays/Displays.hpp"
#include "../../L4_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../L4_DomainModels/LedStrips/LedStrips.hpp"

#include "DomainModelsContext.hpp"

DomainModelsContext::DomainModelsContext() = default;

DomainModelsContext::~DomainModelsContext() = default;

void DomainModelsContext::Set(
    std::unique_ptr<Displays> displays,
    std::unique_ptr<IoPins> ioPins,
    std::unique_ptr<LedStrips> ledStrips
)
{
    _displays = std::move(displays);
    _ioPins = std::move(ioPins);
    _ledStrips = std::move(ledStrips);
}
