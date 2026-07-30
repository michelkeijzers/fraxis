#ifdef ESP_PLATFORM

#include "EspBuilder.hpp"

#include "../../L6_DeviceDrivers/I2c/EspI2cDeviceDriver.hpp"
#include "../../L6_DeviceDrivers/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../../L6_DeviceDrivers/Mcp23017/EspMcp23017DeviceDriver.hpp"
#include "../../L6_DeviceDrivers/Tm1637/EspTm1637DeviceDriver.hpp"
#include "../../L6_DeviceDrivers/Ws28xx/EspWs28xxDeviceDriver.hpp"
#include "../../L8_Services/Rtos/EspRtos.hpp"
#include "../../L8_Services/RtosQueue/EspRtosQueue.hpp"
#include "../../L8_Services/Random/EspRandom.hpp"

EspBuilder::EspBuilder(Context& context)
: Builder(context) 
{
}
    
EspBuilder::~EspBuilder()
{
}

void EspBuilder::BuildDeviceDriversContext()
{
    GetContext().GetDeviceDrivers().Set(
        std::make_unique<EspI2cDeviceDriver>(),
        std::make_unique<Lcd2004DeviceDriver>(), // Not platform specific
        std::make_unique<EspMcp23017DeviceDriver>(),
        std::make_unique<EspTm1637DeviceDriver>(),
        std::make_unique<EspTm1637DeviceDriver>(),
        std::make_unique<EspTm1637DeviceDriver>(),
        std::make_unique<EspWs28xxDeviceDriver>()
    );
}

void EspBuilder::BuildServicesContext()
{
    GetContext().GetServices().Set(
        std::make_unique<EspRtos>(),
        std::make_unique<EspRtosQueue>(10, sizeof(int)),
        std::make_unique<EspRandom>()
    );
}

#endif // ESP_PLATFORM
