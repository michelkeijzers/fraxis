#pragma once

#include "../M40_DomainModels/Audio/I2sMicrophone/I2sMicrophone.hpp"
#include "../M40_DomainModels/Audio/I2sDac/I2sDac.hpp"
#include "../M40_DomainModels/Audio/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../M40_DomainModels/Audio/AudioOutputQueueReader.hpp"
#include "../M60_DeviceDrivers/Audio/AudioTaskDeviceDriversDelegate.hpp"
#include "../M90_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class AudioOutputQueue;

class AudioTask : public M90::Task::Task
{
public:
    explicit AudioTask(
        Context& context,
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities);

    AudioTask(
        const AudioTask&) = delete;
    
    AudioTask& operator=(
        const AudioTask&) = delete;
    
    AudioTask(
        AudioTask&&) = delete;
    
    AudioTask& operator=(
        AudioTask&&) = delete;

    ~AudioTask() override = default;

    void Initialize() override;
    
    void Run() override;
    
    static void TaskEntry(
        void* param);

private:
    Context& _context;
    
    I2sMicrophone& _i2sMicrophone;
    
    I2sDac& _i2sDac;
    
    PassiveBuzzer& _passiveBuzzer;

    AudioOutputQueue& _audioOutputQueue;
    
    AudioOutputQueueReader _audioOutputQueueReader;

    M60::Audio::AudioTaskDeviceDriversDelegate _audioTaskDeviceDriversDelegate;
};
