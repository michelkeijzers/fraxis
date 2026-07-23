#include "../../L8_Services/Rtos/Rtos.hpp"
#include "../../L8_Services/RtosQueue/RtosQueue.hpp"
#include "../../L8_Services/Random/Random.hpp"

#include "ServicesContext.hpp"

ServicesContext::ServicesContext() = default;

ServicesContext::~ServicesContext() = default;

void ServicesContext::Set(std::unique_ptr<Rtos> rtos, std::unique_ptr<RtosQueue> queue, std::unique_ptr<Random> random)
{
    _rtos = std::move(rtos);
    _queue = std::move(queue);
    _random = std::move(random);
}
