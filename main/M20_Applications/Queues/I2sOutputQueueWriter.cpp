#include "I2sOutputQueueWriter.hpp"
#include "../ApplicationsManager.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M30_Messages/I2s/I2sOutputQueue.hpp"
#include "../../M40_DomainModels/I2s/I2sDac//I2sDac.hpp"
#include "../../M40_DomainModels/I2s/I2sMicrophone/I2sMicrophone.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../../M90_Utilities/String/StringUtilities.hpp"

I2sOutputQueueWriter::I2sOutputQueueWriter(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities,
    I2sOutputQueue& i2sOutputQueue,
    ApplicationsManager& applicationsManager)
    :
    QueueProcessor(assert, log, stringUtilities),
    _applicationsManager(applicationsManager)
{
    SetQueue(i2sOutputQueue);
}

I2sOutputQueue& I2sOutputQueueWriter::GetI2sOutputQueue()
{
    return static_cast<I2sOutputQueue&>(GetQueue());
}
