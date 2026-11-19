#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "I2sMicrophone/I2sMicrophone.hpp"
#include "I2sDac/I2sDac.hpp"
#include "PassiveBuzzer/PassiveBuzzer.hpp"

class AudioOutputQueue;

class AudioOutputQueueReader : public QueueProcessor
{
public:
    AudioOutputQueueReader(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities,
        AudioOutputQueue& audioOutputQueue,
        I2sDac& dac,
        PassiveBuzzer& buzzer);

    AudioOutputQueueReader(
        const AudioOutputQueueReader&) = delete;
    
    AudioOutputQueueReader& operator=(
        const AudioOutputQueueReader&) = delete;
    
    AudioOutputQueueReader(
        AudioOutputQueueReader&&) = delete;
    
    AudioOutputQueueReader& operator=(
        AudioOutputQueueReader&&) = delete;

    ~AudioOutputQueueReader() override = default;

    bool HandleMessage();

private:
    AudioOutputQueue& GetAudioOutputQueue();

    I2sDac& _i2sDac;
    
    PassiveBuzzer& _passiveBuzzer;
};
