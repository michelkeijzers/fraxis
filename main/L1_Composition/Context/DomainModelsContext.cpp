#include "../../L4_DomainModels/I2c/Displays/Displays.hpp"
#include "../../L4_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../L4_DomainModels/LedStrips/LedStrips.hpp"

#include "DomainModelsContext.hpp"

DomainModelsContext::DomainModelsContext()
{
}

DomainModelsContext::~DomainModelsContext()
{
}

void DomainModelsContext::Set(
    std::unique_ptr<Displays> displays, std::unique_ptr<IoPins> ioPins, std::unique_ptr<LedStrips> ledStrips)
{
    _displays = std::move(displays);
    _ioPins = std::move(ioPins);
    _ledStrips = std::move(ledStrips);
}

Displays& DomainModelsContext::GetDisplays()             
{
    return *_displays; 
}

IoPins& DomainModelsContext::GetIoPins()                
{
    return *_ioPins; 
}

LedStrips& DomainModelsContext::GetLedStrips()          
{
    return *_ledStrips; 
}
