#pragma once

class OutputQueueWriter;
class LedStripsQueueWriter;

class QueueWriters
{
public:
    QueueWriters(OutputQueueWriter& outputQueueWriter, LedStripsQueueWriter& ledStripsQueueWriter);
    ~QueueWriters();

private:
    OutputQueueWriter& _outputQueueWriter;
    LedStripsQueueWriter& _ledStripsQueueWriter;
};
