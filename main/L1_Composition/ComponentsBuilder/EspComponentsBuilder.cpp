#include "EspComponentsBuilder.hpp"

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
