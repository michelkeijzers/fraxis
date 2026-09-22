#include "NvsQueueWriter.hpp"
#include "../../M80_Services/Nvs/Nvs.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include <string.h>

NvsQueueWriter::NvsQueueWriter(
    NvsQueue& nvsQueue,
    Nvs& nvs)
: 
    QueueProcessor(),
    _nvsQueue(nvsQueue),
    _nvs(nvs)
{
    SetQueue(_nvsQueue);
}
