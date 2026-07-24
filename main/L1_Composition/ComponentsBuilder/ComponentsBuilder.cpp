#include "ComponentsBuilder.hpp"

#include "../../L2_Applications/ApplicationsTask.hpp"

#include "../../L3_Messages/LedStripsQueue.hpp"
#include "../../L3_Messages/InputQueue.hpp"
#include "../../L3_Messages/OutputQueue.hpp"

#include "../../L4_DomainModels/Tasks/LedStripsTask.hpp"
#include "../../L4_DomainModels/Tasks/I2cTask.hpp"

#include "../../L4_DomainModels/IoPins/IoPins.hpp"
#include "../../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../../L4_DomainModels/Tm1637/Tm1637.hpp"
#include "../../L4_DomainModels/Lcd2004/Lcd2004.hpp"

#include "../../L5_DeviceModels/Ws28xx/Ws28xxModel.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017Model.hpp"
#include "../../L5_DeviceModels/Lcd2004/Lcd2004Model.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637Model.hpp"

ComponentsBuilder::~ComponentsBuilder() = default;

void ComponentsBuilder::Build(Context& context)
{
    BuildDomainModelsContext(context);
    BuildDeviceModelsContext(context);
    BuildDeviceDriversContext(context);
    BuildServicesContext(context);
}

void ComponentsBuilder::BuildDomainModelsContext(Context& context)
{
    context.GetDomainModels().Set(
        std::make_unique<LedStrips>(),
        std::make_unique<IoPins>(),
        std::make_unique<Lcd2004>(),
        std::make_unique<Tm1637>(),
        std::make_unique<Tm1637>(),
        std::make_unique<Tm1637>()
    );
}

void ComponentsBuilder::BuildDeviceModelsContext(Context& context)
{
    context.GetDeviceModels().Set(
        std::make_unique<Ws28xxModel>(),
        std::make_unique<Mcp23017Model>(),
        std::make_unique<Lcd2004Model>(),
        std::make_unique<Tm1637Model>(),
        std::make_unique<Tm1637Model>(),
        std::make_unique<Tm1637Model>()
    );
}


void ComponentsBuilder::BuildRtosTasks(Context& context)
{
    context.GetRtosTasks().Set(
        std::make_unique<ApplicationsTask>(context),
        std::make_unique<I2cTask>(context),
        std::make_unique<LedStripsTask>(context)
    );
}

void ComponentsBuilder::BuildRtosQueues(Context& context)
{
    context.GetRtosQueues().Set(
        std::make_unique<LedStripsQueue>(),
        std::make_unique<InputQueue>(),
        std::make_unique<OutputQueue>());
}
