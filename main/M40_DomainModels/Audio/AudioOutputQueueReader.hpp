#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "Microphone/Inmp1441.hpp"
#include "Dac/Max53987a.hpp"
#include "Buzzer/Buzzer.hpp"

class AudioOutputQueue;

class AudioOutputQueueReader : public QueueProcessor
{
public:
    AudioOutputQueueReader(
        AudioOutputQueue& audioOutputQueue,
        Max53987a& dac,
        Buzzer& buzzer);

    AudioOutputQueueReader(const AudioOutputQueueReader&) = delete;
    AudioOutputQueueReader& operator=(const AudioOutputQueueReader&) = delete;
    AudioOutputQueueReader(AudioOutputQueueReader&&) = delete;
    AudioOutputQueueReader& operator=(AudioOutputQueueReader&&) = delete;

    ~AudioOutputQueueReader() override = default;

    bool HandleMessage();

private:
    AudioOutputQueue& GetAudioOutputQueue();

    Max53987a& _dac;
    Buzzer& _buzzer;
};
