#include "AudioOutputQueueReader.hpp"
#include "../../M30_Messages/Audio/AudioOutputQueue.hpp"

AudioOutputQueueReader::AudioOutputQueueReader(
    AudioOutputQueue& audioOutputQueue,
    Max53987a& dac,
    Buzzer& buzzer)
: QueueProcessor(),
  _dac(dac),
  _buzzer(buzzer)
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
            _dac.WriteSamples(message.playSamples.buffer, message.playSamples.length);
            break;
        }
        case AudioOutputQueue::Message::EType::PlayWavFile:
        {
            break;
        }
        case AudioOutputQueue::Message::EType::PlayBuzzer:
        {
            _buzzer.Start();
            break;
        }
        case AudioOutputQueue::Message::EType::StopBuzzer:
        {
            _buzzer.Stop();
            break;
        }
        case AudioOutputQueue::Message::EType::SetBuzzerFrequency:
        {
            _buzzer.SetFrequency(message.setBuzzerFrequency.frequency);
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
