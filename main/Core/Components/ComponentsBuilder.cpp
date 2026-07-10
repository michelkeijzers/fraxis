#include "ComponentsBuilder.hpp"
#include "../../Core/Components/LedStrips.hpp"
#include "../../Core/Components/PinIo.hpp"
#include "../../Common/Components/LedStrip/LedStripModel.hpp"

ComponentsBuilder::ComponentsBuilder()
    : _fraxisComponents({ }), _models({ }), _drivers({ } )
{
}

void ComponentsBuilder::Build()
{
    BuildModels(); 
    BuildDrivers();
    BuildFraxisComponents();
}

void ComponentsBuilder::BuildModels()
{
    _models.ledStripModel = new LedStripModel(LedStrips::NUMBER_OF_LEDS);
}

void ComponentsBuilder::BuildFraxisComponents()
{
    _fraxisComponents.ledStrips = new LedStrips(*(_models.ledStripModel));
    _fraxisComponents.pinIo = new PinIo(*(_drivers.mcp23017));
};

