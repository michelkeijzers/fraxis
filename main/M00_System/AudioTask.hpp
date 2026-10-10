#pragma once

#include "../M40_DomainModels/Audio/Microphone/Inmp1441.hpp"
#include "../M40_DomainModels/Audio/Dac/Max53987a.hpp"
#include "../M40_DomainModels/Audio/Buzzer/Buzzer.hpp"
#include "../M30_Messages/Audio/AudioOutputQueueReader.hpp"
#include "../M60_DeviceDrivers/Audio/AudioTaskDeviceDriversDelegate.hpp"
#include "../M90_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class AudioOutputQueue;

class AudioTask : public Task
{
public:
    explicit AudioTask(
        Context& context);
    ~AudioTask() = default;

    void Initialize() override;
    void Run() override;
    static void TaskEntry(
        void* param);

private:
    Context& _context;
    Inmp1441& _microphone;
    Max53987a& _dac;
    Buzzer& _buzzer;

    AudioOutputQueue& _audioOutputQueue;
    AudioOutputQueueReader _audioOutputQueueReader;

    AudioTaskDeviceDriversDelegate _audioTaskDeviceDriversDelegate;
};
