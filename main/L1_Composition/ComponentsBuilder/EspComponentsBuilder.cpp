#include "EspComponentsBuilder.hpp"

#include "../../L4_DomainModels/IoPins/IoPins.hpp"
#include "../../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../../L4_DomainModels/Tm1637/Tm1637.hpp"
#include "../../L4_DomainModels/Lcd2004/Lcd2004.hpp"

#include "../../L5_DeviceModels/Ws28xx/Ws28xxModel.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017Model.hpp"
#include "../../L5_DeviceModels/Lcd2004/Lcd2004Model.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637Model.hpp"

#include "../../L6_DeviceDrivers/Ws28xx/EspWs28xxDriver.hpp"
#include "../../L6_DeviceDrivers/I2c/EspI2cDriver.hpp"
#include "../../L6_DeviceDrivers/Mcp23017/EspMcp23017Driver.hpp"
#include "../../L6_DeviceDrivers/Lcd2004/EspLcd2004Driver.hpp"
#include "../../L6_DeviceDrivers/Tm1637/EspTm1637Driver.hpp"

#include "../../L8_Services/Rtos/EspRtos.hpp"
#include "../../L8_Services/RtosQueue/EspRtosQueue.hpp"
#include "../../L8_Services/Random/EspRandom.hpp"

EspComponentsBuilder::EspComponentsBuilder() = default;
    
EspComponentsBuilder::~EspComponentsBuilder() = default;


void EspComponentsBuilder::BuildDomainModelsContext(Context& context)
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

void EspComponentsBuilder::BuildDeviceModelsContext(Context& context)
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

void EspComponentsBuilder::BuildDeviceDriversContext(Context& context)
{
    context.GetDeviceDrivers().Set(
        std::make_unique<EspWs28xxDriver>(),
        std::make_unique<EspI2cDriver>(),
        std::make_unique<EspMcp23017Driver>(),
        std::make_unique<EspLcd2004Driver>(),
        std::make_unique<EspTm1637Driver>(),
        std::make_unique<EspTm1637Driver>(),
        std::make_unique<EspTm1637Driver>()
    );
}

void EspComponentsBuilder::BuildServicesContext(Context& context)
{
    context.GetServices().Set(
        std::make_unique<EspRtos>(),
        std::make_unique<EspRtosQueue>(10, sizeof(int)),
        std::make_unique<EspRandom>()
    );
}
