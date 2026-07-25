#include "LedStripsQueueWriter.hpp"
#include "../../L3_Messages/LedStripsQueue.hpp"
#include "../ApplicationsManager.hpp"

LedStripsQueueWriter::LedStripsQueueWriter(LedStripsQueue& ledStripsQueue, ApplicationsManager& applicationsManager) 
: _ledStripsQueue(ledStripsQueue), _applicationsManager(applicationsManager)
{
}

LedStripsQueueWriter::~LedStripsQueueWriter()
{
}
