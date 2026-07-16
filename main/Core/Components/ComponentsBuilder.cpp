#include "ComponentsBuilder.hpp"
#include "../../Core/Components/LedStrips.hpp"
#include "../../Core/Components/PinIo.hpp"
#include "../../Common/Components/LedStrip/LedStripModel.hpp"
#include "../../Common/Components/Lcd1602Display/Lcd1602DisplayModel.hpp"

ComponentsBuilder::ComponentsBuilder()
    : _fraxisComponents({ }), _models({ }), _drivers({ } )
{
}

void ComponentsBuilder::Build()
{
    BuildModels(); 
    BuildDrivers(_models);
    BuildFraxisComponents();
}

void ComponentsBuilder::BuildModels()
{
    _models.ledStripModel = new LedStripModel(LedStrips::NUMBER_OF_LEDS);
    _models.lcd1602DisplayModel = new Lcd1602DisplayModel();
}

void ComponentsBuilder::BuildFraxisComponents()
{
    _fraxisComponents.ledStrips = new LedStrips(*(_models.ledStripModel));
    _fraxisComponents.pinIo = new PinIo(*(_drivers.mcp23017));
};

