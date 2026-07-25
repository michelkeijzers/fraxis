#include "OutputQueueWriter.hpp"
#include "../../L3_Messages/OutputQueue.hpp"
#include "../ApplicationsManager.hpp"

OutputQueueWriter::OutputQueueWriter(OutputQueue& outputQueue, ApplicationsManager& applicationsManager) 
: _outputQueue(outputQueue), _applicationsManager(applicationsManager)
{
}

OutputQueueWriter::~OutputQueueWriter()
{
}
