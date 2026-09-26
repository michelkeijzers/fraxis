#ifdef ESP_PLATFORM

#include "EspBuilder.hpp"

#include "../../M80_Services/Gpio/EspGpio.hpp"
#include "../../M80_Services/I2c/EspI2c.hpp"
#include "../../M80_Services/Spi/EspSpi.hpp"
#include "../../M80_Services/Rmt/EspRmt.hpp"
#include "../../M81_RtosServices/Rtos/EspRtos.hpp"
#include "../../M81_RtosServices/RtosQueue/EspRtosQueue.hpp"
#include "../../M80_Services/Random/EspRandom.hpp"
#include "../../M80_Services/Uart/EspUart.hpp"
#include "../../M80_Services/Nvs/EspNvs.hpp"


EspBuilder::EspBuilder(
    Context& context)
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
        std::make_unique<EspSpi>(),
        std::make_unique<EspRmt>(),
        std::make_unique<EspRandom>(),
        std::make_unique<EspUart>(),
        std::make_unique<EspNvs>());
}

#endif // ESP_PLATFORM
