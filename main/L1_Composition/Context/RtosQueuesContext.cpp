#include "../../L8_Services/RtosTask/RtosTask.hpp"

#include "RtosQueuesContext.hpp"
#include "../../L3_Messages/LedStripsQueue.hpp"
#include "../../L3_Messages/InputQueue.hpp"
#include "../../L3_Messages/OutputQueue.hpp"

RtosQueuesContext::RtosQueuesContext() = default;

RtosQueuesContext::~RtosQueuesContext() = default;

void RtosQueuesContext::Set(
    std::unique_ptr<LedStripsQueue> ledStripsQueue,
    std::unique_ptr<InputQueue> inputQueue,
    std::unique_ptr<OutputQueue> outputQueue)
{
    _ledStripsQueue = std::move(ledStripsQueue);
    _inputQueue = std::move(inputQueue);
    _outputQueue = std::move(outputQueue);
}
