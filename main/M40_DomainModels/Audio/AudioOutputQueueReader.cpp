#include "AudioOutputQueueReader.hpp"
#include "../../M30_Messages/Audio/AudioOutputQueue.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"

AudioOutputQueueReader::AudioOutputQueueReader(
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities,
    AudioOutputQueue& audioOutputQueue,
    I2sDac& i2sDac,
    PassiveBuzzer& passiveBuzzer)
:
    QueueProcessor(assert, stringUtilities),
    _i2sDac(i2sDac),
    _passiveBuzzer(passiveBuzzer)
{
    SetQueue(audioOutputQueue);
}

bool AudioOutputQueueReader::HandleMessage()
{
    AudioOutputQueue::Message message;
    if (!GetAudioOutputQueue().GetRtosQueue().Receive(&message, 0))
    {
        return false;
    }

    switch (message.type)
    {
        case AudioOutputQueue::Message::EType::PlaySamples:
        {
            _i2sDac.WriteSamples(message.playSamples.buffer, message.playSamples.length);
            break;
        }
        case AudioOutputQueue::Message::EType::PlayWavFile:
        {
            break;
        }
        case AudioOutputQueue::Message::EType::PlayBuzzer:
        {
            _passiveBuzzer.Start();
            break;
        }
        case AudioOutputQueue::Message::EType::StopBuzzer:
        {
            _passiveBuzzer.Stop();
            break;
        }
        case AudioOutputQueue::Message::EType::SetBuzzerFrequency:
        {
            _passiveBuzzer.SetFrequency(message.setBuzzerFrequency.frequency);
            break;
        }
        default:
            break;
    }

    return true;
}

AudioOutputQueue& AudioOutputQueueReader::GetAudioOutputQueue()
{
    return static_cast<AudioOutputQueue&>(GetQueue());
}
