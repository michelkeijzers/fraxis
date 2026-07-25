#pragma once
#include <cstdint>
#include <string>

class QueueWriters;

class Send
{
public:
    Send(QueueWriters& queueWriters);
    ~Send();

    void Line(uint8_t lineNumber, std::string line);

private:
    QueueWriters& _queueWriters;
};
