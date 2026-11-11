#include "AudioTask.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../M90_Utilities/Log/Log.hpp"

AudioTask::AudioTask(
    Context& context)
:   
    _context(context),
    _microphone(context.GetDomainModels().GetMicrophone()),
    _dac(context.GetDomainModels().GetDac()),
    _buzzer(context.GetDomainModels().GetBuzzer()),
    _audioOutputQueue(_context.GetQueues().GetAudioOutputQueue()),
    _audioOutputQueueReader(_audioOutputQueue, _dac, _buzzer),
    _audioTaskDeviceDriversDelegate(context)
{
}

void AudioTask::Initialize()
{
    _audioTaskDeviceDriversDelegate.Initialize();
}

void AudioTask::Run()
{
    M90::Log::Log::Entry(Types::ETaskId::AudioTask, "AudioTask::Run()");
    while (true)
    {
        while (_audioOutputQueueReader.HandleMessage())
        {
            // NOSONAR TODO I2S
        }

        _audioTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    M90::Log::Log::Exit(Types::ETaskId::AudioTask, "AudioTask::Run()");
}

void AudioTask::TaskEntry(
    void* param) // NOSONAR S5008: replace void*
{
    auto* self = static_cast<AudioTask*>(param);
    self->Run();
}
