#include "ComponentsBuilder.hpp"

ComponentsBuilder::~ComponentsBuilder() = default;

void ComponentsBuilder::Build(Context& context)
{
    BuildDomainModelsContext(context);
    BuildDeviceModelsContext(context);
    BuildDeviceDriversContext(context);
    BuildServicesContext(context);
}
