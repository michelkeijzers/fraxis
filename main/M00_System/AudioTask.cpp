#include "AudioTask.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../M90_Utilities/Log/Log.hpp"

AudioTask::AudioTask(
    Context& context,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities)
:   
    Task(log),
    _context(context),
    _i2sMicrophone(context.GetDomainModels().GetI2sMicrophone()),
    _i2sDac(context.GetDomainModels().GetI2sDac()),
    _passiveBuzzer(context.GetDomainModels().GetPassiveBuzzer()),
    _audioOutputQueue(_context.GetQueues().GetAudioOutputQueue()),
    _audioOutputQueueReader(assert, stringUtilities, _audioOutputQueue, _i2sDac, _passiveBuzzer),
    _audioTaskDeviceDriversDelegate(context)
{
}

void AudioTask::Initialize()
{
    _audioTaskDeviceDriversDelegate.Initialize();
}

void AudioTask::Run()
{
    GetLog().Entry(Types::ETaskId::AudioTask, "AudioTask::Run()");
    while (true)
    {
        while (_audioOutputQueueReader.HandleMessage())
        {
            // NOSONAR TODO I2S
        }

        _audioTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    GetLog().Exit(Types::ETaskId::AudioTask, "AudioTask::Run()");
}

void AudioTask::TaskEntry(
    void* param) // NOSONAR S5008: replace void*
{
    auto* self = static_cast<AudioTask*>(param);
    self->Run();
}
