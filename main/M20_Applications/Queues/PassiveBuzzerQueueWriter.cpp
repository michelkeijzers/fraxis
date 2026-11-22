#include "PassiveBuzzerQueueWriter.hpp"
#include "../ApplicationsManager.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M30_Messages/PassiveBuzzer/PassiveBuzzerQueue.hpp"
#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../../M90_Utilities/String/StringUtilities.hpp"

PassiveBuzzerQueueWriter::PassiveBuzzerQueueWriter(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities,
    PassiveBuzzerQueue& passiveBuzzerQueue,
    ApplicationsManager& applicationsManager)
    :
    QueueProcessor(assert, log, stringUtilities),
    _applicationsManager(applicationsManager)
{
    SetQueue(passiveBuzzerQueue);
}

PassiveBuzzerQueue& PassiveBuzzerQueueWriter::GetPassiveBuzzerQueue()
{
    return static_cast<PassiveBuzzerQueue&>(GetQueue());
}
