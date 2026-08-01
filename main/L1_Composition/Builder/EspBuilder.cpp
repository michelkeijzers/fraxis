#ifdef ESP_PLATFORM

#include "EspBuilder.hpp"

#include "../../L8_Services/Gpio/EspGpio.hpp"
#include "../../L8_Services/I2c/EspI2c.hpp"
#include "../../L8_Services/Rmt/EspRmt.hpp"
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

void EspBuilder::BuildServicesContext()
{
    GetContext().GetServices().Set(
        std::make_unique<EspRtos>(),
        std::make_unique<EspGpio>(),
        std::make_unique<EspI2c>(),
        std::make_unique<EspRmt>(),
        std::make_unique<EspRandom>()
    );
}

#endif // ESP_PLATFORM
